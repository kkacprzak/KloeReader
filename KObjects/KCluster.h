#include <TVector3.h>


/**
 * Class containting Cluster objects
 */
class KCluster : public TObject
{
public:
  KCluster(){};
  ~KCluster(){};

  void setID(Int_t id){ fID = id; }
  void setEnergy(Float_t energy){ fEnergy = energy; }
  void setAverageTime(Float_t averageTime){ fAverageTime = averageTime; }
  void setPosition(TVector3 clusterPosition){ fClusterPosition = clusterPosition; }

private:
  Int_t fID;
  Float_t fEnergy;
  Float_t fAverageTime;
  TVector3 fClusterPosition;

  ClassDef(KCluster, 1);
};
