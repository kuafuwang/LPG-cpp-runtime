#pragma once
#include <vector>
#include <unordered_map>

struct IPrsStream;

class Differ
{
public:
	virtual ~Differ()
	{
        for (auto& it : change_pool)
        {
            delete it;
        }
	}
	//
    // Class that encodes the meaningful content of a line.
    //
  
    struct  Change
    {
        friend class Differ;
        int number,
            olds,
            olde,
            news,
            newe,
            code,

            temp,
            temp2;

        Change* next;



        int getCode() { return code; }
        int getOlds() { return olds; }
        int getOlde() { return olde; }
        int getNews() { return news; }
        int getNewe() { return newe; }
        int getNumber() { return number; }

        int getTemp() { return temp; }
        int getTemp2() { return temp2; }

        Change* getNext() { return next; }

        void setCode(int code) { this->code = code; }
        void setOlds(int olds) { this->olds = olds; }
        void setOlde(int olde) { this->olde = olde; }
        void setNews(int news) { this->news = news; }
        void setNewe(int newe) { this->newe = newe; }
        void setNumber(int number) { this->number = number; }

        void setTemp(int temp) { this->temp = temp; }
        void setTemp2(int temp2) { this->temp2 = temp2; }

        void setNext(Change* next) { this->next = next; }

    private:
        Change(int code, int olds, int olde, int news, int newe, int number) : temp(0), temp2(0), next(nullptr)
        {
            this->code = code;
            this->olds = olds;
            this->olde = olde;
            this->news = news;
            this->newe = newe;
            this->number = number;
        }
    };
    struct  ILine
    {
	    virtual ~ILine() = default;

	    virtual int size()=0;
        virtual int getStartLine()=0;
        virtual int getStartColumn()=0;
        virtual int getEndLine()=0;
        virtual int getEndColumn()=0;
        virtual  bool equals(ILine* anObject)=0;
    };

    //
    // Class to store a difference between two sections in the files.
    //
   
	Change* getChangeInstance(int code, int olds, int olde, int news, int newe, int number)
	{
      auto ins =   new Change(code, olds, olde, news, newe, number);
      change_pool.push_back(ins);
      return  ins;
	}
    std::vector<Change*> change_pool;
    //
    // The codes for the different kinds of Change*s.
    //
   const  static int I_CODE = 0;
   const  static int D_CODE = 1;
   const  static int R_CODE = 2;
   const  static int M_CODE = 3;
   const  static int MM_CODE = 4;
   const  static int IMI_CODE = 5;
   const  static int MI_CODE = 6;
   const  static int IM_CODE = 7;
   const  static int DMD_CODE = 8;
   const  static int MD_CODE = 9;
   const  static int DM_CODE = 10;

   IPrsStream* newStream;
   IPrsStream* oldStream;

    int insertCount = 0,
        deleteCount = 0,
        replaceDeleteCount = 0,
        replaceInsertCount = 0,
        moveCount = 0;

    Change * deleteRoot = nullptr;
    Change* insertRoot = nullptr;
    Change* replaceRoot = nullptr;
    Change* changeRoot  = nullptr;

    int changeCount = 0,
        extraCount = 0;

    int newStart,
        oldStart,
        newEnd,
        oldEnd;

    std::vector<ILine*> newBuffer;
    std::vector<ILine*>   oldBuffer;

    std::unordered_map<ILine*, int> newMap;
    std::vector<int>newLink;

     virtual std::vector<ILine*>  getBuffer(IPrsStream* stream)=0;

    Differ(): newStream(nullptr), oldStream(nullptr), newStart(0), oldStart(0), newEnd(0), oldEnd(0)
	{
	}

	Differ( IPrsStream* newStream,IPrsStream* oldStream);

     int min(int x, int y) { return x < y ? x : y; }

      int getChangeCount() { return changeCount; }

      int getInsertCount() { return insertCount; }
      int getDeleteCount() { return deleteCount; }
      int getReplaceDeleteCount() { return replaceDeleteCount; }
      int getReplaceInsertCount() { return replaceInsertCount; }
      int getMoveCount() { return moveCount; }

    void compare();

    //
    // This procedure outputs the differences found between the two files*/
    //
    void outputChanges();

    //
    // In this procedure,the section of text from a stream identified
    // by the indices start..end is removed from its hash map.
    //
    void detach(std::vector<ILine*>& buffer, std::unordered_map<ILine*, int>& map, std::vector<int>& link, int start,
                int end);

    //
    // This function tests whether two sections of text are identical
    //
    bool compareSections(int olds, int news, int bound);

    //
    // This procedure takes 4 integer argumets that indicate a section
    // of the old file that was replaced by a section of the new file.
    // We first analyze the given Change* to see if in fact it is not a
    // disguised Move.  If it is a cross-Move we update the old Replace
    // that makes it so, and add a new Move.  Otherwise, we add a new
    // Replace Change*.
    //
    void addReplace(int olds, int olde, int news, int newe);

    //
    // In this procedure, we search for identical sections of text that
    // were deleted from one place and inserted into another, and
    // combine these Change*s into Move Change*s.
    //
    void findMoves();

    //
    // The procedure COMPARE takes four arguments OLDS and OLDE which    
    // mark the start and end indices of old lines in the buffer to be
    // compared to new lines in the buffer indicated by NEWS and NEWE
    // which respectively mark the new start and end indices.
    //
    void compare(int olds, int olde, int news, int newe);

    //
    // This function receives two pointers as parameters: D and I.
    // D identifies a Delete Change*, and I an Insert Change*. The Change*s
    // are known to contain the same number of lines.  The objective is
    // to check wheter the Change*s are identical or that they are each
    // separated into two segments that have been interChange*d,  but
    // identical.
    //
    bool similarSections(Change* d_element, Change* i_element);

    //
    // In this function, we check whether an Insert section overlaps a
    // Delete section.
    //
    bool insertOverlap(Change* d_element, Change* i_element);

    //
    // In this function, we check whether a Delete section overlaps an
    // Insert section.
    //
    bool deleteOverlap(Change* d_element, Change* i_element);

    //
    // This procedure merges the separate lists of Change*s which are
    // contained in linear linked lists identified by the pointers:
    // Change*_ROOT, INSERT_ROOT, DELETE_ROOT, and REPLACE_ROOT into a
    // separate list pointed to by Change*_ROOT.
    //
    void mergeChanges();

    virtual void outputInsert(Change* element)=0;
    virtual void outputDelete(Change* element)=0;
    virtual void outputReplace(Change* element)=0;
    virtual void outputMove(Change* element)=0;
    virtual void outputMoveDelete(Change* element)=0;
    virtual void outputMoveInsert(Change* element)=0;
protected:
    void init();
};
