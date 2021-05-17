#include "Differ.h"

#include <iostream>

Differ::Differ( IPrsStream* newStream, IPrsStream* oldStream): newStart(0), oldStart(0), newEnd(0), oldEnd(0)
{
	this->newStream = newStream;
	this->oldStream = oldStream;
}

void Differ::compare()
{
	if (newLink.size())
	{
		compare(oldStart, oldEnd, newStart, newEnd);
		findMoves();
		mergeChanges();
	}

	return;
}

void Differ::outputChanges()
{
	for (Change* element = changeRoot; element != nullptr; element = element->getNext())
	{
		if (element->getCode() == I_CODE)
			outputInsert(element);
		else if (element->getCode() == D_CODE)
			outputDelete(element);
		else if (element->getCode() == R_CODE)
			outputReplace(element);
		else if (element->getCode() == M_CODE)
			outputMove(element);
		else if (element->getCode() == MD_CODE)
			outputMoveDelete(element);
		else if (element->getCode() == MI_CODE)
			outputMoveInsert(element);
		else
		{
			std::cout << "Don't know what to do with code ";
			std::cout << element->getCode() << std::endl;
		}
			
	}

	return;
}

void Differ::detach(std::vector<ILine*>& buffer, std::unordered_map<ILine*, int>& map, std::vector<int>& link,
                    int start, int end)
{
	for (int k = start; k <= end; k++)
	{
		auto line = buffer[k];
		int root;
		auto findIt = map.find(line);
		if (findIt != map.end())
		{
			root = findIt->second;
			int previous = 0;
			for (int i = root; i != k && i != 0; previous = i, i = link[i]);
			if (previous == 0)
			{
				int successor = link[root];
				if (successor == 0)
					map.erase(line);
				else
				{
					map[line] = successor;
				}
				
			}
			else link[previous] = link[k];
		}
	}

	return;
}

bool Differ::compareSections(int olds, int news, int bound)
{
	for (int i = 0; i <= bound; i++)
	{
		if (!oldBuffer[olds + i]->equals(newBuffer[news + i]))
			return false;
	}

	return true;
}

void Differ::addReplace(int olds, int olde, int news, int newe)
{
	changeCount++;
	detach(newBuffer, newMap, newLink, news, newe);
	Change* element = replaceRoot;
	Change* tail = nullptr;
	for (;element != nullptr; tail = element, element = element->getNext())
	{
		int bound1 = (element->getOlde() - element->getOlds()),
			bound2 = (element->getNewe() - element->getNews());
		if (bound1 == (newe - news) && bound2 == (olde - olds))
		{
			if (compareSections(element->getOlds(), news, bound1))
			{
				if (compareSections(olds, element->getNews(), bound2))
				{
					Change* change_element = getChangeInstance(M_CODE, element->getOlds(), element->getOlde(), news, newe, changeCount);
					change_element->setNext(changeRoot);
					changeRoot = change_element;

					element->setCode(M_CODE);
					element->setOlds(olds);
					element->setOlde(olde);
					if (element == replaceRoot)
						replaceRoot = element->getNext();
					else tail->setNext(element->getNext());

					element->setNext(changeRoot);
					changeRoot = element;

					return;
				}
			}
		}
	}

	element = getChangeInstance(R_CODE, olds, olde, news, newe, changeCount);
	element->setNext(replaceRoot);
	replaceRoot = element;

	return;
}

void Differ::findMoves()
{
	Change * i_element;
	Change *d_element;
	Change *previous_d;
	Change *previous_i;

	//
	// For each deletion, we search the insertion list for an identical
	// or similar section that was inserted in another location.  If so,
	// these changes are turned into Move changes.
	// The function similarSections takes care of the comparison, and
	// if it finds that the two sections are similar, it then updates
	// the Insert node and turns it into a Move or Move_Move.
	//
	for (i_element = insertRoot, previous_i = nullptr; i_element != nullptr && deleteRoot != nullptr; previous_i = i_element, i_element = i_element->getNext())
	{
		int bound = i_element->getNewe() - i_element->getNews();

		for (d_element = deleteRoot, previous_d = nullptr; d_element != nullptr; previous_d = d_element, d_element = d_element->getNext())
		{
			if (bound == d_element->getOlde() - d_element->getOlds())
			{
				if (similarSections(d_element, i_element))
				{
					if (d_element == deleteRoot)
						deleteRoot = d_element->getNext();
					else previous_d->setNext(d_element->getNext());
					break;
				}
			}
		}

		if (i_element->getCode() != I_CODE)
		{
			if (i_element == insertRoot)
				insertRoot = i_element->getNext();
			else previous_i->setNext(i_element->getNext());

			i_element->setNext(changeRoot);
			changeRoot = i_element;
		}
	}

	//
	// We now look for Delete sections that overlap Insert sections.
	// The Delete section must contain at least 3 lines to be considered.
	// The function DELETE_OVERLAP is invoked to do the check.  If a
	// successful overlap is found, the Delete node is changed into the
	// the appropriate DM, MD, or DMD change.
	//
	for (d_element = deleteRoot, previous_d = nullptr; d_element != nullptr && insertRoot != nullptr; previous_d = d_element, d_element = d_element->getNext())
	{
		int bound = d_element->getOlde() - d_element->getOlds();
		if (bound >= 2) // At least 3 lines?
		{
			for (i_element = insertRoot; i_element != nullptr; previous_i = i_element, i_element = i_element->getNext())
			{
				if (bound < i_element->getNewe() - i_element->getNews())
				{
					if (deleteOverlap(d_element, i_element))
					{
						if (i_element == insertRoot)
							insertRoot = i_element->getNext();
						else previous_i->setNext(i_element->getNext());
						break;
					}
				}
			}

			if (d_element->getCode() != D_CODE)
			{
				if (d_element == deleteRoot)
					deleteRoot = d_element->getNext();
				else previous_d->setNext(d_element->getNext());

				d_element->setNext(changeRoot);
				changeRoot = d_element;
			}
		}
	}

	//
	// We now look for Insert sections that overlap Delete sections.
	// The Insert section must contain at least 3 lines to be considered.
	// The function INSERT_OVERLAP is invoked to do the check.  If a
	// successful overlap is found, the Insert node is changed into the
	// the appropriate IM, MI, or IMI change.
	//
	for (i_element = insertRoot, previous_i = nullptr; i_element != nullptr && deleteRoot != nullptr; previous_i = i_element, i_element = i_element->getNext())
	{
		int bound = i_element->getNewe() - i_element->getNews();
		if (bound >= 2) // At least 3 lines?
		{
			for (d_element = deleteRoot, previous_d = nullptr; d_element != nullptr; previous_d = d_element, d_element = d_element->getNext())
			{
				if (bound < d_element->getOlde() - d_element->getOlds())
				{
					if (insertOverlap(d_element, i_element))
					{
						if (d_element == deleteRoot)
							deleteRoot = d_element->getNext();
						else previous_d->setNext(d_element->getNext());
						break;
					}
				}
			}
		}

		if (i_element->getCode() != I_CODE)
		{
			if (i_element == insertRoot)
				insertRoot = i_element->getNext();
			else previous_i->setNext(i_element->getNext());

			i_element->setNext(changeRoot);
			changeRoot = i_element;
		}
	}

	return;
}

void Differ::compare(int olds, int olde, int news, int newe)
{
	//
	 // At this stage, We know that we are dealing with two sections
	 // which differ by at least their first line. If the end of both
	 // sections was reached, we simply return.
	 //
	if (olds > olde && news > newe) // end of both sections?
		return;

	if (olds > olde) // End of old section?
	{
		changeCount++;
		Change* element = getChangeInstance(I_CODE, olds, olde, news, newe, changeCount);
		element->setNext(insertRoot);
		insertRoot = element;
		detach(newBuffer, newMap, newLink, news, newe);
	}
	else if (news > newe) // End of new section?
	{
		changeCount++;
		Change* element = getChangeInstance(D_CODE, olds, olde, news, newe, changeCount);
		element->setNext(deleteRoot);
		deleteRoot = element;
	}
	else // Find largest subsection that matches
	{
		int largest = 0, // keeps track of size of matched subsection
			lolds = 0,
			lnews = 0;

		//
		// Start OLDI at OLDS and move forward while OLDI has
		// a chance to beat the previous largest subsection.
		//
		for (int oldi = olds; oldi + largest <= olde; oldi++)
		{
			auto findIt = newMap.find(oldBuffer[oldi]); // list of OLDI lines
			if (findIt != newMap.end())
			{
				int image = findIt->second;
				for (int newi = image; newi != 0 && oldi + largest <= olde; newi = newLink[newi])
				{
					if (newi >= news && newi + largest <= newe)
					{
						if (oldBuffer[oldi + largest]->equals(newBuffer[newi + largest]))
						{
							// Any chance to do better than before?
							int bound = min(newe - newi, olde - oldi),
								i;
							for (i = 1; i <= bound; i++)
							{
								if (!oldBuffer[oldi + i]->equals(newBuffer[newi + i]))
									break;
							}
							if (i > largest)
							{
								largest = i;
								lolds = oldi;
								lnews = newi;
							}
						}
					}
				}
			}
		}

		if (largest > 0)
		{
			//
			// A matched subsection was found. It starts at index
			// LOLDS for the old file, and LNEWS for the new file,
			// and contains LARGEST records.
			//
			detach(newBuffer, newMap, newLink, lnews, lnews + largest - 1);
			compare(olds, lolds - 1, news, lnews - 1);
			compare(lolds + largest, olde, lnews + largest, newe);
		}
		else addReplace(olds, olde, news, newe);
	}

	return;
}

bool Differ::similarSections(Change* d_element, Change* i_element)
{
	std::unordered_map<ILine*, int> map;
	std::vector<int>  link(newBuffer.size(), 0);
	std::vector<int>tail(newBuffer.size(), 0);

	//
	// We first check whether the two sections are identical, then we
	// check whether they do not contain nullptr lines only...
	//
	int bound = d_element->getOlde() - d_element->getOlds();
	if (compareSections(d_element->getOlds(), i_element->getNews(), bound))
	{
		for (int i = d_element->getOlds(); i <= d_element->getOlde(); i++)
		{
			if (!(oldBuffer[i]->size() == 0)) // Not all the lines are nullptrs
			{
				i_element->setCode(M_CODE);
				i_element->setOlds(d_element->getOlds());
				i_element->setOlde(d_element->getOlde());
				extraCount++;

				return true;
			}
		}

		return false; // All the lines are nullptr
	}

	//
	// We first insert all the lines from the new file into the hash
	// table for quick look up.  We then attempt to locate a subsection
	// in the bottom part of the new sections that matches the upper
	// part of the old section.  If we are successful, we then check
	// whether the bottom portion of the old section matches the upper
	// part of the new section.
	//
	for (int i = i_element->getNews(); i <= i_element->getNewe(); i++)
	{
		ILine* line = newBuffer[i];
		int root;
		auto  findIt=map.find(line);
		if (findIt == map.end())
		{
			root = i;
			map.insert({ line, root });
		}
		else
		{
			root = findIt->second;
			link[tail[root]] = i;
		}

		tail[root] = i;
	}

	int largest = -1,
	    newi = 0;
	bound = 0;
	int image;
	auto findIt = map.find(oldBuffer[d_element->getOlds()]);
	if (findIt != map.end())
	{
		image = findIt->second;
		for (int j = image; j != 0; j = link[j])
		{
			bound = i_element->getNewe() - j;
			if (compareSections(d_element->getOlds(), j, bound))
			{
				if (bound > largest)
				{
					largest = bound;
					newi = j;
				}
			}
		}
	}

	detach(newBuffer, map, link, i_element->getNews(), i_element->getNewe());

	if (largest >= 0) // We found a matched segment.
	{
		i_element->setTemp(bound); // Save old offset
		int oldi = d_element->getOlds() + bound + 1;
		bound = d_element->getOlde() - oldi;
		if (compareSections(oldi, i_element->getNews(), bound)) // Does the other segment compare
		{
			//
			// We mark the Change* as MM to indicate that it really
			// represents two Moves.  The OLDE field marks the end
			// point of the old section that matches the last line
			// in the new section. The TEMP field marks the beginning
			// of the second old segment and the TEMP2 field marks
			// the beginning of the second new segment.
			// In the procedure MERGE_Change*S, the Change*s marked MM
			// are broken down into two separate Moves.
			//
			i_element->setCode(MM_CODE);
			i_element->setOlds(d_element->getOlds());
			i_element->setOlde(d_element->getOlde());
			i_element->setTemp(oldi);
			i_element->setTemp2(newi);

			return true;
		}
	}

	return false;
}

bool Differ::insertOverlap(Change* d_element, Change* i_element)
{
	std::unordered_map<ILine*, int> map;
	std::vector<int>  link(oldBuffer.size(), 0);
	std::vector<int>tail(oldBuffer.size(), 0);
	//
	// We first insert all the lines from the Delete section into the
	// table for quick look up.  We then look to see if the Insert
	// section overlaps the Delete section.  If so, we update the Insert
	// change to reflect the new changes.
	//
	for (int i = d_element->getOlds(); i <= d_element->getOlde(); i++)
	{
		ILine *line = oldBuffer[i];
		int root;
		auto findIt = map.find(line);
		if (findIt == map.end())
		{
			root = i;
			map.insert({ line, root });
		}
		else {
			root = findIt->second;
			link[tail[root]] = i;
		}

		tail[root] = i;
	}
	int oldi = 0,
		bound = i_element->getNewe() - i_element->getNews();
	int image = 0;
	auto findIt = map.find(oldBuffer[i_element->getNews()]);
	if (findIt != map.end())
	{
		image = findIt->second;
		for (oldi = image; oldi != 0; oldi = link[oldi])
		{
			if (d_element->getOlde() - oldi >= bound)
			{
				if (compareSections(oldi, i_element->getNews(), bound))
					break;
			}
		}
	}

	detach(oldBuffer, map, link, d_element->getOlds(), d_element->getOlde());

	if (oldi != 0) //  We found a matched segment.
	{
		if (oldi == d_element->getOlds())
		{
			extraCount++;
			i_element->setCode(MD_CODE);
		}
		else if (d_element->getOlde() == oldi + bound)
			i_element->setCode(DM_CODE);
		else i_element->setCode(DMD_CODE);
		i_element->setTemp(oldi);
		i_element->setTemp2(d_element->getNewe());
		i_element->setOlds(d_element->getOlds());
		i_element->setOlde(d_element->getOlde());

		return true;
	}

	return false;
}

bool Differ::deleteOverlap(Change* d_element, Change* i_element)
{
	std::unordered_map<ILine*, int> map;
	std::vector<int>  link(newBuffer.size(), 0);
	std::vector<int>tail(newBuffer.size(), 0);

	//
	// We first insert all the lines from the Insert section into the
	// table for quick look up.  We then look to see if the Delete
	// section overlaps the Insert section.  If so, we update the Insert
	// change to reflect the new changes.
	//
	for (int i = i_element->getNews(); i <= i_element->getNewe(); i++)
	{
		ILine *line = newBuffer[i];
		int root;
		auto findIt  =map.find(line);
		if (findIt == map.end())
		{
		
			root = i;
			map.insert({ line, root });
		}
		else
		{
			root = findIt->second;
			link[tail[root]] = i;
		}

		tail[root] = i;
	}

	int bound = d_element->getOlde() - d_element->getOlds(),
		newi = 0;

	int image;
	auto findIt= map.find(oldBuffer[d_element->getOlds()]);
	if (findIt != map.end())
	{
		image = findIt->second;
		for (newi = image; newi != 0; newi = link[newi])
		{
			if (i_element->getNewe() - newi >= bound)
			{
				if (compareSections(d_element->getOlds(), newi, bound))
					break;
			}
		}
	}

	detach(newBuffer, map, link, i_element->getNews(), i_element->getNewe());

	if (newi != 0) //  We found a matched segment.
	{
		if (newi == i_element->getNews())
		{
			extraCount++;
			d_element->setCode(MI_CODE);
		}
		else if (i_element->getNewe() == newi + bound)
			d_element->setCode(IM_CODE);
		else d_element->setCode(IMI_CODE);
		d_element->setTemp(newi);
		d_element->setTemp2(i_element->getOlde());
		d_element->setNews(i_element->getNews());
		d_element->setNewe(i_element->getNewe());

		return true;
	}

	return false;
}

void Differ::mergeChanges()
{
	std::vector<Change*>  change(changeCount + 1,nullptr);
	std::vector<bool >slot_used(changeCount + 1,false);

	//
	// In this loop, We make each element I of the array CHANGE point to
	// change number I.
	//
	for (Change* element = insertRoot; element != nullptr; element = element->getNext())
	{
		change[element->getNumber()] = element;
		slot_used[element->getNumber()] = true;
	}
	for (Change* element = deleteRoot; element != nullptr; element = element->getNext())
	{
		change[element->getNumber()] = element;
		slot_used[element->getNumber()] = true;
	}
	for (Change *element = replaceRoot; element != nullptr; element = element->getNext())
	{
		change[element->getNumber()] = element;
		slot_used[element->getNumber()] = true;
	}
	for (Change *element = changeRoot; element != nullptr; element = element->getNext())
	{
		change[element->getNumber()] = element;
		slot_used[element->getNumber()] = true;
	}

	//
	// We loop backwards on the array of changes and insert them into a
	// new linear linked list in a stack fashion so as to preserve the
	// correct ordering.
	//
	changeRoot = nullptr;
	for (int i = changeCount; i >= 1; i--)
	{
		if (slot_used[i])
		{
			//
			// Changes marked MM represent two contiguous Moves. The
			// old lines are marked by the fields OLDS, and OLDE.
			// The new lines are marked by the fields NEWS, and NEWE.
			// The temporary field TEMP marks the first line in the
			// the second segment of the old lines; and TEMP2 marks
			// the first line in the second segment of the new lines.
			// We know that the first segment of the old line is
			// identical to the second segment of the new lines.
			//
			if (change[i]->getCode() == MM_CODE)
			{
				Change *element = getChangeInstance(M_CODE,
					change[i]->getOlds(),
					change[i]->getTemp() - 1,
					change[i]->getTemp2(),
					change[i]->getNewe(),
					change[i]->getNumber());
				element->setNext(changeRoot);
				changeRoot = element;

				change[i]->setCode(M_CODE);
				change[i]->setOlds(change[i]->getTemp());
				change[i]->setNewe(change[i]->getTemp2() - 1);
			}
			//
			// TEMP marks the beginning of the Move segment, and
			// TEMP2 marks the new line after which the deletion
			// took place.
			//
			else if (change[i]->getCode() == DM_CODE)
			{
				Change* element = getChangeInstance(M_CODE,
					change[i]->getTemp(),
					change[i]->getOlde(),
					change[i]->getNews(),
					change[i]->getNewe(),
					change[i]->getNumber());
				element->setNext(changeRoot);
				changeRoot = element;

				change[i]->setCode(D_CODE);
				change[i]->setOlde(change[i]->getTemp() - 1);
				change[i]->setNewe(change[i]->getTemp2());
			}
			//
			// Same as DM except that the Move is followed by
			// another Delete.
			//
			else if (change[i]->getCode() == DMD_CODE)
			{
				Change* element = getChangeInstance(MD_CODE,
					change[i]->getTemp(),
					change[i]->getOlde(),
					change[i]->getNews(),
					change[i]->getNewe(),
					change[i]->getNumber());
				element->setNext(changeRoot);
				changeRoot = element;

				change[i]->setCode(D_CODE);
				change[i]->setOlde(change[i]->getTemp() - 1);
				change[i]->setNewe(change[i]->getTemp2());
			}
			//
			// TEMP marks the beginning of the Move segment, and
			// TEMP2 marks the old line after which the initial
			// Insertion was made.
			//
			else if (change[i]->getCode() == IM_CODE)
			{
				Change *element = getChangeInstance(M_CODE,
					change[i]->getOlds(),
					change[i]->getOlde(),
					change[i]->getTemp(),
					change[i]->getNewe(),
					change[i]->getNumber());
				element->setNext(changeRoot);
				changeRoot = element;

				change[i]->setCode(I_CODE);
				change[i]->setNewe(change[i]->getTemp() - 1);
				change[i]->setOlde(change[i]->getTemp2());
			}
			//
			// Same as IM except that the Move is followed by
			// another Insert.
			//
			else if (change[i]->getCode() == IMI_CODE)
			{
				Change *element = getChangeInstance(MI_CODE,
					change[i]->getOlds(),
					change[i]->getOlde(),
					change[i]->getTemp(),
					change[i]->getNewe(),
					change[i]->getNumber());
				element->setNext(changeRoot);
				changeRoot = element;

				change[i]->setCode(I_CODE);
				change[i]->setNewe(change[i]->getTemp() - 1);
				change[i]->setOlde(change[i]->getTemp2());
			}

			change[i]->setNext(changeRoot);
			changeRoot = change[i];
		}
	}

	changeCount -= extraCount;

	return;

}

void Differ::init()
{

	
	int i,
		k;
	for (i = 1; i < newBuffer.size() && i < oldBuffer.size(); i++)
	{
		if (!(newBuffer[i]->equals(oldBuffer[i])))
			break;
	}

	if (i == newBuffer.size() && i == oldBuffer.size())
		return;

	newStart = i;
	oldStart = i;

	for (i = newBuffer.size() - 1, k = oldBuffer.size() - 1;
		i > newStart && k > oldStart;
		i--, k--)
	{
		if (!(newBuffer[i]->equals(oldBuffer[k])))
			break;
	}

	newEnd = i;
	oldEnd = k;

	newLink.resize(newBuffer.size());
	std::vector<int> tail(newBuffer.size(), 0);
	for (i = 1; i < newBuffer.size(); i++)
	{
		ILine* line = newBuffer[i];
		int root;
		auto findIt = newMap.find(line);
		if (findIt == newMap.end())
		{
			root = i;
			newMap.insert({ line, root });
		}
		else
		{
			root = findIt->second;
			newLink[tail[root]] = i;
		}

		tail[root] = i;
	}
}
