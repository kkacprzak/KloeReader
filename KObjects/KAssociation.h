#include <TLorentzVector.h>
#include <TVector3.h>

/**
 * Class containting Track and Cluster objects and info about their association
 */
class KAssociation : public TObject
{
public:
  KAssociation(){};
  ~KAssociation(){};

  void setTrackInfo(
    Int_t trackID, Int_t dstIndex, Float_t curvature, Float_t phiAngle,
    Float_t cotanTheta, Float_t trackLength, TLorentzVector momentum,
    TVector3 firstHit, TVector3 lastHit
  ){
    fTrackID = trackID;
    fDSTIndex = dstIndex;
    fCurvature = curvature;
    fPhiAngle = phiAngle;
    fCotanTheta = cotanTheta;
    fTrackLength = trackLength;
    fMomentum = momentum;
    fFirstHit = firstHit;
    fLastHit = lastHit;
  }

  void setClusterInfo(
    Int_t clusterID, Float_t energy, Float_t averageTime, TVector3 position
  ){
    fClusterID = clusterID;
    fEnergy = energy;
    fAverageTime = averageTime;
    fPosition = position;
  }

  void setAssociationInfo(
    Int_t associationID, Float_t associationLength,
    Float_t chi2, TVector3 extrapolation
  ){
    fAssociationID = associationID;
    fAssociationLength = associationLength;
    fChi2 = chi2;
    fExtrapolation = extrapolation;
  }

private:
  // Track
  Int_t fTrackID;
  Int_t fDSTIndex;
  Float_t fCurvature;
  Float_t fPhiAngle;
  Float_t fCotanTheta;
  Float_t fTrackLength;
  TLorentzVector fMomentum;
  TVector3 fFirstHit;
  TVector3 fLastHit;

  // Cluster
  Int_t fClusterID;
  Float_t fEnergy;
  Float_t fAverageTime;
  TVector3 fPosition;

  // Association
  Int_t fAssociationID;
  Float_t fAssociationLength;
  Float_t fChi2;
  TVector3 fExtrapolation;

  ClassDef(KAssociation, 1);
};
