#include <TLorentzVector.h>
#include <TVector3.h>

/**
 * Class containting Track objects
 */
class KTrack : public TObject
{
public:
  KTrack(){};
  ~KTrack(){};

  void setID(Int_t id){ fID = id; }
  void setTrackIndex(Int_t tkrIndex){ fTrackIndex = tkrIndex; }
  void setCurvature(Float_t curvature){ fCurvature = curvature; }
  void setPhiAngle(Float_t phiAngle){ fPhiAngle = phiAngle; }
  void setContanTheta(Float_t cotanTheta){ fCotanTheta = cotanTheta; }
  void setTrakcLength(Float_t trackLength){ fTrackLength = trackLength; }
  void setMomentum4Vector(TLorentzVector momentum){ fMomentum = momentum; }
  void setFirstHit(TVector3 firstHit){ fFirstHit = firstHit; }
  void setLastHit(TVector3 lastHit){ fLastHit = lastHit; }

private:
  Int_t fID;
  Int_t fTrackIndex;
  Float_t fCurvature;
  Float_t fPhiAngle;
  Float_t fCotanTheta;
  Float_t fTrackLength;
  TLorentzVector fMomentum;
  TVector3 fFirstHit;
  TVector3 fLastHit;

  ClassDef(KTrack, 1);
};
