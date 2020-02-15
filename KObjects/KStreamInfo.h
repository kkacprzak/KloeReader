/**
 * Class containting info about stream, tag and event type
 */
class KStreamInfo : public TObject
{
public:
  KStreamInfo(){};
  ~KStreamInfo(){};

  void setID(Int_t id){ fID = id; }
  void setWord(Int_t word){ fWord = word; }
  void setStream(Int_t stream){ fStream = stream; }
  void setTagNum(Int_t tagNum){ fTagNum = tagNum; }
  void setEventType(Int_t eventType){ fEventType = eventType; }

private:
  Int_t fID;
  Int_t fWord;
  Int_t fStream;
  Int_t fTagNum;
  Int_t fEventType;

  ClassDef(KStreamInfo, 1);
};
