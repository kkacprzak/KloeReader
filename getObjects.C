#include "KObjects/KAssociation.h"
#include "KObjects/KStreamInfo.h"
#include "KObjects/KCluster.h"
#include "KObjects/KTrack.h"
#define MAX 50

{
  ////////////////////////////////////////////
  // Modify here
  const char* dirname = "kaon_26";
  const char *ext=".root";
  int maxInputFiles = 2;
  TString outputName = "K26.root";
  int printFrac = 10000;
  bool saveTracks = true;
  bool saveClusters = true;
  bool saveAssociations = true;
  bool printMessages = true;

  /////////////////////////////////////////////////////////////////////////////
  // Creating chain of files from gicen directory
  TChain* chain = new TChain("PROD2NTU/h1");

  TSystemDirectory dir(dirname, dirname);
  TList *files = dir.GetListOfFiles();

  if (files) {
    TSystemFile *file;
    TString fname;
    TIter next(files);
    int fileCounter = 0;
    while ((file=(TSystemFile*)next()) && fileCounter < maxInputFiles) {
      fname = file->GetName();
      if (!file->IsDirectory() && fname.EndsWith(ext)) {
        std::string buf(dirname);
        buf.append("/");
        buf.append(fname.Data());
        chain->Add(buf.c_str());
        fileCounter++;
      }
    }
    if(printMessages) {
      std::cout << "Added " << fileCounter << " files to analysis chain." << std::endl;
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  // Initialising blocks of data
  // numbering and iterators for separate bocks
  Int_t nrun, nev, necls, necls2, nt, ntold, nclu, ntcl, ntclold;

  // Stream and tag variables
  Int_t Eclword[MAX], Eclstream[MAX], Ecltagnum[MAX], Eclevtype[MAX];
  Int_t Eclword2[MAX], Eclstream2[MAX], Ecltagnum2[MAX], Eclevtype2[MAX];

  // Tracks
  Int_t trkind[MAX], verver[MAX];
  Float_t Cur[MAX], Phi[MAX], Cot[MAX], pxt[MAX], pyt[MAX], pzt[MAX], pmod[MAX], len[MAX];
  Float_t xfirst[MAX], yfirst[MAX], zfirst[MAX], xlast[MAX], ylast[MAX], zlast[MAX];

  // Tracks - old version - Drift Chamber without Inner Tracker
  Int_t trkindold[MAX], ververold[MAX];
  Float_t Curold[MAX], Phiold[MAX], Cotold[MAX];
  Float_t pxtold[MAX], pytold[MAX], pztold[MAX], pmodold[MAX], lenold[MAX];
  Float_t xfirstold[MAX], yfirstold[MAX], zfirstold[MAX];
  Float_t xlastold[MAX], ylastold[MAX], zlastold[MAX];

  // Clusters
  Float_t Enecl[MAX], Tcl[MAX], Xcl[MAX], Ycl[MAX], Zcl[MAX];

  // Asociations - new
  UShort_t Asstr[MAX];
  UChar_t Asscl[MAX];
  Float_t xext[MAX], yext[MAX], zext[MAX], Assleng[MAX], Asschi[MAX];

  // Asociations - old
  UShort_t Asstrold[MAX];
  UChar_t Assclold[MAX];
  Float_t xextold[MAX], yextold[MAX], zextold[MAX];
  Float_t Asslengold[MAX], Asschiold[MAX];

  // General information about measurement
  TBranch *b_nrun = chain->Branch("nrun", &nrun, "nrun/I");
  chain->SetBranchAddress("nrun", &nrun);
  TBranch *b_nev = chain->Branch("nev", &nev, "nev/I");
  chain->SetBranchAddress("nev", &nev);
  TBranch *b_necls = chain->Branch("necls", &necls, "necls/I");
  chain->SetBranchAddress("necls", &necls);
  TBranch *b_necls2 = chain->Branch("necls2", &necls2, "necls2/I");
  chain->SetBranchAddress("necls2", &necls2);

  // Stream, tag and event type, two versions
  TBranch *b_Eclword = chain->Branch("Eclword", &Eclword, "Eclword[necls]/I");
  chain->SetBranchAddress("Eclword", &Eclword);
  TBranch *b_Eclstream = chain->Branch("Eclstream", &Eclstream, "Eclstream[necls]/I");
  chain->SetBranchAddress("Eclstream", &Eclstream);
  TBranch *b_Ecltagnum = chain->Branch("Ecltagnum", &Ecltagnum, "Ecltagnum[necls]/I");
  chain->SetBranchAddress("Ecltagnum", &Ecltagnum);
  TBranch *b_Eclevtype = chain->Branch("Eclevtype", &Eclevtype, "Eclevtype[necls]/I");
  chain->SetBranchAddress("Ecltagnum", &Ecltagnum);

  TBranch *b_Eclword2 = chain->Branch("Eclword2", &Eclword2, "Eclword2[necls2]/I");
  chain->SetBranchAddress("Eclword2", &Eclword2);
  TBranch *b_Eclstream2 = chain->Branch("Eclstream2", &Eclstream2, "Eclstream2[necls2]/I");
  chain->SetBranchAddress("Eclstream2", &Eclstream2);
  TBranch *b_Ecltagnum2 = chain->Branch("Ecltagnum2", &Ecltagnum2, "Ecltagnum2[necls2]/I");
  chain->SetBranchAddress("Ecltagnum2", &Ecltagnum2);
  TBranch *b_Eclevtype2 = chain->Branch("Eclevtype2", &Eclevtype2, "Eclevtype2[necls2]/I");
  chain->SetBranchAddress("Ecltagnum2", &Ecltagnum2);

  // Reconstructed tracks block - new with DC and IT, old with DC only
  TBranch *b_nt = chain->Branch("nt", &nt, "nt/I");
  chain->SetBranchAddress("nt", &nt);
  TBranch *b_trkind = chain->Branch("trkind", &trkind, "trkind[nt]/I");
  chain->SetBranchAddress("trkind", &trkind);

  TBranch *b_Cur = chain->Branch("Cur", &Cur, "Cur[nt]/F");
  chain->SetBranchAddress("Cur", &Cur);
  TBranch *b_Phi = chain->Branch("Phi", &Phi, "Phi[nt]/F");
  chain->SetBranchAddress("Phi", &Phi);
  TBranch *b_Cot = chain->Branch("Cot", &Cot, "Cot[nt]/F");
  chain->SetBranchAddress("Cot", &Cot);
  TBranch *b_pxt = chain->Branch("pxt", &pxt, "pxt[nt]/F");
  chain->SetBranchAddress("pxt", &pxt);
  TBranch *b_pyt = chain->Branch("pyt", &pyt, "pyt[nt]/F");
  chain->SetBranchAddress("pyt", &pyt);
  TBranch *b_pzt = chain->Branch("pzt", &pzt, "pzt[nt]/F");
  chain->SetBranchAddress("pzt", &pzt);
  TBranch *b_pmod = chain->Branch("pmod", &pmod, "pmod[nt]/F");
  chain->SetBranchAddress("pmod", &pmod);
  TBranch *b_len = chain->Branch("len", &len, "len[nt]/F");
  chain->SetBranchAddress("len", &len);

  TBranch *b_xfirst = chain->Branch("xfirst", &xfirst, "xfirst[nt]/F");
  chain->SetBranchAddress("xfirst", &xfirst);
  TBranch *b_yfirst = chain->Branch("yfirst", &yfirst, "yfirst[nt]/F");
  chain->SetBranchAddress("yfirst", &yfirst);
  TBranch *b_zfirst = chain->Branch("zfirst", &zfirst, "zfirst[nt]/F");
  chain->SetBranchAddress("zfirst", &zfirst);
  TBranch *b_xlast = chain->Branch("xlast", &xlast, "xlast[nt]/F");
  chain->SetBranchAddress("xlast", &xlast);
  TBranch *b_ylast = chain->Branch("ylast", &ylast, "ylast[nt]/F");
  chain->SetBranchAddress("ylast", &ylast);
  TBranch *b_zlast = chain->Branch("zlast", &zlast, "zlast[nt]/F");
  chain->SetBranchAddress("zlast", &zlast);

  // Reconstructed tracks block - OLD
  TBranch *b_ntold = chain->Branch("ntold", &ntold, "ntold/I");
  chain->SetBranchAddress("ntold", &ntold);
  TBranch *b_trkindold = chain->Branch("trkindold", &trkindold, "trkindold[ntold]/I");
  chain->SetBranchAddress("trkindold", &trkindold);

  TBranch *b_Curold = chain->Branch("Curold", &Curold, "Curold[ntold]/F");
  chain->SetBranchAddress("Curold", &Curold);
  TBranch *b_Phiold = chain->Branch("Phiold", &Phiold, "Phiold[ntold]/F");
  chain->SetBranchAddress("Phiold", &Phiold);
  TBranch *b_Cotold = chain->Branch("Cotold", &Cotold, "Cotold[ntold]/F");
  chain->SetBranchAddress("Cotold", &Cotold);
  TBranch *b_pxtold = chain->Branch("pxtold", &pxtold, "pxtold[ntold]/F");
  chain->SetBranchAddress("pxtold", &pxtold);
  TBranch *b_pytold = chain->Branch("pytold", &pytold, "pytold[ntold]/F");
  chain->SetBranchAddress("pytold", &pytold);
  TBranch *b_pztold = chain->Branch("pztold", &pztold, "pztold[ntold]/F");
  chain->SetBranchAddress("pztold", &pztold);
  TBranch *b_pmodold = chain->Branch("pmodold", &pmodold, "pmodold[ntold]/F");
  chain->SetBranchAddress("pmodold", &pmodold);
  TBranch *b_lenold = chain->Branch("lenold", &lenold, "lenold[ntold]/F");
  chain->SetBranchAddress("lenold", &lenold);

  TBranch *b_xfirstold = chain->Branch("xfirstold", &xfirstold, "xfirstold[ntold]/F");
  chain->SetBranchAddress("xfirstold", &xfirstold);
  TBranch *b_yfirstold = chain->Branch("yfirstold", &yfirstold, "yfirstold[ntold]/F");
  chain->SetBranchAddress("yfirstold", &yfirstold);
  TBranch *b_zfirstold = chain->Branch("zfirstold", &zfirstold, "zfirstold[ntold]/F");
  chain->SetBranchAddress("zfirstold", &zfirstold);
  TBranch *b_xlastold = chain->Branch("xlastold", &xlastold, "xlastold[ntold]/F");
  chain->SetBranchAddress("xlastold", &xlastold);
  TBranch *b_ylastold = chain->Branch("ylastold", &ylastold, "ylastold[ntold]/F");
  chain->SetBranchAddress("ylastold", &ylastold);
  TBranch *b_zlastold = chain->Branch("zlastold", &zlastold, "zlastold[ntold]/F");
  chain->SetBranchAddress("zlastold", &zlastold);

  // Clusters block
  TBranch *b_nclu = chain->Branch("nclu", &nclu, "nclu/I");
  chain->SetBranchAddress("nclu", &nclu);

  TBranch *b_Enecl = chain->Branch("Enecl", &Enecl, "Enecl[nclu]/F");
  chain->SetBranchAddress("Enecl", &Enecl);
  TBranch *b_Tcl = chain->Branch("Tcl", &Tcl, "Tcl[nclu]/F");
  chain->SetBranchAddress("Tcl", &Tcl);
  TBranch *b_Xcl = chain->Branch("Xcl", &Xcl, "Xcl[nclu]/F");
  chain->SetBranchAddress("Xcl", &Xcl);
  TBranch *b_Ycl = chain->Branch("Ycl", &Ycl, "Ycl[nclu]/F");
  chain->SetBranchAddress("Ycl", &Ycl);
  TBranch *b_Zcl = chain->Branch("Zcl", &Zcl, "Zcl[nclu]/F");

  // Assiciations of tracks and clusters
  TBranch *b_ntcl = chain->Branch("ntcl", &ntcl, "ntcl/I");
  chain->SetBranchAddress("ntcl", &ntcl);
  TBranch *b_Asstr = chain->Branch("Asstr", &Asstr, "Asstr[ntcl]/s");
  chain->SetBranchAddress("Asstr", &Asstr);
  TBranch *b_Asscl = chain->Branch("Asscl", &Asscl, "Asscl[ntcl]/b");
  chain->SetBranchAddress("Asscl", &Asscl);
  TBranch *b_xext = chain->Branch("xext", &xext, "xext[ntcl]/F");
  chain->SetBranchAddress("xext", &xext);
  TBranch *b_yext = chain->Branch("yext", &yext, "yext[ntcl]/F");
  chain->SetBranchAddress("yext", &yext);
  TBranch *b_zext = chain->Branch("zext", &zext, "zext[ntcl]/F");
  chain->SetBranchAddress("zext", &zext);
  TBranch *b_Assleng = chain->Branch("Assleng", &Assleng, "Assleng[ntcl]/F");
  chain->SetBranchAddress("Assleng", &Assleng);
  TBranch *b_Asschi = chain->Branch("Asschi", &Asschi, "Asschi[ntcl]/F");
  chain->SetBranchAddress("Asschi", &Asschi);
  TBranch *b_verver = chain->Branch("verver", &verver, "verver[ntcl]/I");
  chain->SetBranchAddress("verver", &verver);

  // Assiciations of OLD tracks and clusters
  TBranch *b_ntclold = chain->Branch("ntclold", &ntclold, "ntclold/I");
  chain->SetBranchAddress("ntclold", &ntclold);
  TBranch *b_Asstrold = chain->Branch("Asstrold", &Asstrold, "Asstrold[ntclold]/s");
  chain->SetBranchAddress("Asstrold", &Asstrold);
  TBranch *b_Assclold = chain->Branch("Assclold", &Assclold, "Assclold[ntclold]/b");
  chain->SetBranchAddress("Assclold", &Assclold);
  TBranch *b_xextold = chain->Branch("xextold", &xextold, "xextold[ntclold]/F");
  chain->SetBranchAddress("xextold", &xextold);
  TBranch *b_yextold = chain->Branch("yextold", &yextold, "yextold[ntclold]/F");
  chain->SetBranchAddress("yextold", &yextold);
  TBranch *b_zextold = chain->Branch("zextold", &zextold, "zextold[ntclold]/F");
  chain->SetBranchAddress("zextold", &zextold);
  TBranch *b_Asslengold = chain->Branch("Asslengold", &Asslengold, "Asslengold[ntclold]/F");
  chain->SetBranchAddress("Asslengold", &Asslengold);
  TBranch *b_Asschiold = chain->Branch("Asschiold", &Asschiold, "Asschiold[ntclold]/F");
  chain->SetBranchAddress("Asschiold", &Asschiold);
  TBranch *b_ververold = chain->Branch("ververold", &ververold, "ververold[ntclold]/I");
  chain->SetBranchAddress("ververold", &ververold);

  // end of ntuple blocks
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // Reading entries and writing to file as objects of custom classes

  Int_t runNum, evtNum, evtID, numTrack, numTrackOld;
  Int_t numCluster, numAssociation, numAssociationOld, numStremInfo, numStremInfo2;

  KStreamInfo* streamInfo;
  KStreamInfo* streamInfo2;
  KTrack* track;
  KTrack* track_old;
  KCluster* cluster;
  KAssociation* association;
  KAssociation* association_old;

  // Output file and tree setup
  TFile* outputFile = new TFile(outputName, "RECREATE");

  TTree* streamInfoTree = new TTree("KStreamInfo", "A tree with Stream Info");
  TTree* streamInfo2Tree = new TTree("KStreamInfoOld", "A tree with Stream Info 2");
  TTree* tracksTree = new TTree("KTracks", "A tree with Tracks");
  TTree* tracksOldTree = new TTree("KTracksOld", "A tree with old Tracks");
  TTree* clustersTree = new TTree("KClusters", "A tree with Clusters");
  TTree* associationTree = new TTree("KAssociations", "A tree with Associations");
  TTree* associationOldTree = new TTree("KAssociationsOld", "A tree with old Associations");

  streamInfoTree->Branch("strInfo", &streamInfo, 16000, 99);
  streamInfoTree->Branch("evtID", &evtID, 16000, 99);
  streamInfoTree->Branch("runNum", &runNum, 16000, 99);
  streamInfoTree->Branch("evtNum", &evtNum, 16000, 99);
  streamInfoTree->Branch("numTrack", &numTrack, 16000, 99);
  streamInfoTree->Branch("numTrackOld", &numTrackOld, 16000, 99);
  streamInfoTree->Branch("numAssociation", &numAssociation, 16000, 99);
  streamInfoTree->Branch("numAssociationOld", &numAssociationOld, 16000, 99);
  streamInfoTree->Branch("numStremInfo", &numStremInfo, 16000, 99);
  streamInfoTree->Branch("numStremInfo2", &numStremInfo2, 16000, 99);

  streamInfo2Tree->Branch("strInfo", &streamInfo2, 16000, 99);
  streamInfo2Tree->Branch("evtID", &evtID, 16000, 99);
  streamInfo2Tree->Branch("runNum", &runNum, 16000, 99);
  streamInfo2Tree->Branch("evtNum", &evtNum, 16000, 99);

  tracksTree->Branch("tracks", &track, 16000, 99);
  tracksTree->Branch("evtID", &evtID, 16000, 99);
  tracksTree->Branch("runNum", &runNum, 16000, 99);
  tracksTree->Branch("evtNum", &evtNum, 16000, 99);

  tracksOldTree->Branch("tracks", &track_old, 16000, 99);
  tracksOldTree->Branch("evtID", &evtID, 16000, 99);
  tracksOldTree->Branch("runNum", &runNum, 16000, 99);
  tracksOldTree->Branch("evtNum", &evtNum, 16000, 99);

  clustersTree->Branch("cluters", &cluster, 16000, 99);
  clustersTree->Branch("evtID", &evtID, 16000, 99);
  clustersTree->Branch("runNum", &runNum, 16000, 99);
  clustersTree->Branch("evtNum", &evtNum, 16000, 99);

  associationTree->Branch("association", &association, 16000, 99);
  associationTree->Branch("evtID", &evtID, 16000, 99);
  associationTree->Branch("runNum", &runNum, 16000, 99);
  associationTree->Branch("evtNum", &evtNum, 16000, 99);

  associationOldTree->Branch("association", &association_old, 16000, 99);
  associationOldTree->Branch("evtID", &evtID, 16000, 99);
  associationOldTree->Branch("runNum", &runNum, 16000, 99);
  associationOldTree->Branch("evtNum", &evtNum, 16000, 99);

  // Adding friend trees to first stream info
  streamInfoTree->AddFriend(streamInfo2Tree);
  streamInfoTree->AddFriend(tracksTree);
  streamInfoTree->AddFriend(tracksOldTree);
  streamInfoTree->AddFriend(clustersTree);
  streamInfoTree->AddFriend(associationTree);
  streamInfoTree->AddFriend(associationOldTree);

  Int_t nevent = chain->GetEntries();
  for (Int_t i=0; i<nevent; i++) {

    if(printMessages && i%printFrac==0) {
      std::cout << 100.0*i/nevent << " % " << std::endl;
    }

    chain->GetEvent(i);

    // Iterate over stream info
    for(Int_t necls_i = 0; necls_i<necls; necls_i++){

      evtID = i;
      runNum = nrun;
      evtNum = nev;
      numTrack = nt;
      numTrackOld = ntold;
      numCluster = nclu;
      numAssociation = ntcl;
      numAssociationOld = ntclold;
      numStremInfo = necls;
      numStremInfo2 = necls2;

      streamInfo = new KStreamInfo();
      streamInfo->setID(necls_i);
      streamInfo->setWord(Eclword[necls_i]);
      streamInfo->setStream(Eclstream[necls_i]);
      streamInfo->setTagNum(Ecltagnum[necls_i]);
      streamInfo->setEventType(Eclevtype[necls_i]);
      streamInfoTree->Fill();
    }

    for(Int_t necls2_i = 0; necls2_i<necls2; necls2_i++){

      evtID = i;
      runNum = nrun;
      evtNum = nev;

      streamInfo2 = new KStreamInfo();
      streamInfo2->setID(necls2_i);
      streamInfo2->setWord(Eclword2[necls2_i]);
      streamInfo2->setStream(Eclstream2[necls2_i]);
      streamInfo2->setTagNum(Ecltagnum2[necls2_i]);
      streamInfo2->setEventType(Eclevtype2[necls2_i]);
      streamInfo2Tree->Fill();
    }

    if(saveTracks){
      // Iterating over tracks
      for(Int_t nt_i = 0; nt_i<nt; nt_i++){

        evtID = i;
        runNum = nrun;
        evtNum = nev;

        TLorentzVector momentum;
        TVector3 tmpVec(pxt[nt_i], pyt[nt_i], pzt[nt_i]);
        momentum.SetVectMag(tmpVec, pmod[nt_i]);
        TVector3 firstHit(xfirst[nt_i], yfirst[nt_i], zfirst[nt_i]);
        TVector3 lastHit(xlast[nt_i], ylast[nt_i], zlast[nt_i]);

        track = new KTrack();
        track->setID(nt_i);
        track->setTrackIndex(trkind[nt_i]);
        track->setCurvature(Cur[nt_i]);
        track->setPhiAngle(Phi[nt_i]);
        track->setContanTheta(Cot[nt_i]);
        track->setTrakcLength(len[nt_i]);
        track->setMomentum4Vector(momentum);
        track->setFirstHit(firstHit);
        track->setLastHit(lastHit);
        tracksTree->Fill();
      }

      // Iterating over old tracks
      for(Int_t ntold_i = 0; ntold_i<ntold; ntold_i++){
        evtID = i;
        runNum = nrun;
        evtNum = nev;

        TLorentzVector momentum_old;
        TVector3 tmpVec_old(pxtold[ntold_i], pytold[ntold_i], pztold[ntold_i]);
        momentum_old.SetVectMag(tmpVec_old, pmodold[ntold_i]);
        TVector3 firstHit_old(xfirstold[ntold_i], yfirstold[ntold_i], zfirstold[ntold_i]);
        TVector3 lastHit_old(xlastold[ntold_i], ylastold[ntold_i], zlastold[ntold_i]);

        track_old = new KTrack();
        track_old->setID(ntold_i);
        track_old->setTrackIndex(trkindold[ntold_i]);
        track_old->setCurvature(Curold[ntold_i]);
        track_old->setPhiAngle(Phiold[ntold_i]);
        track_old->setContanTheta(Cotold[ntold_i]);
        track_old->setTrakcLength(lenold[ntold_i]);
        track_old->setMomentum4Vector(momentum_old);
        track_old->setFirstHit(firstHit_old);
        track_old->setLastHit(lastHit_old);
        tracksOldTree->Fill();
      }
    }

    if(saveClusters){
      // Iterating over clusters
      for(Int_t nclu_i = 0; nclu_i<nclu; nclu_i++){

        evtID = i;
        runNum = nrun;
        evtNum = nev;

        TVector3 position(Xcl[nclu_i], Ycl[nclu_i], Zcl[nclu_i]);

        cluster = new KCluster();
        cluster->setID(nclu_i);
        cluster->setEnergy(Enecl[nclu_i]);
        cluster->setAverageTime(Tcl[nclu_i]);
        cluster->setPosition(position);
        clustersTree->Fill();
      }
    }

    if(saveAssociations){

      // Iterating over associations
      for(Int_t ntcl_i = 0; ntcl_i<ntcl; ntcl_i++){
        if(verver[ntcl_i] == 10) { continue; }

        evtID = i;
        runNum = nrun;
        evtNum = nev;

        // associated clutster ID
        Int_t cluID = ((Int_t) Asscl[ntcl_i]);

        // Track number (nt) is different than track index (trkind)
        // Asstr[ntcl] has the same value as trkind[nt], iterating over (nt)
        Int_t trkID = -1;
        for(Int_t nt_i = 0; nt_i<nt; nt_i++){
          if(Asstr[ntcl_i] == trkind[nt_i]) { trkID = nt_i; }
        }

        TVector3 extrapolation(xext[ntcl_i], yext[ntcl_i], zext[ntcl_i]);
        TLorentzVector momentum;
        TVector3 tmpVec(pxt[trkID], pyt[trkID], pzt[trkID]);
        momentum.SetVectMag(tmpVec, pmod[trkID]);
        TVector3 firstHit(xfirst[trkID], yfirst[trkID], zfirst[trkID]);
        TVector3 lastHit(xlast[trkID], ylast[trkID], zlast[trkID]);
        TVector3 clusterPosition(Xcl[cluID], Ycl[cluID], Zcl[cluID]);

        association = new KAssociation();
        association->setTrackInfo(
          trkID, trkind[trkID], Cur[trkID], Phi[trkID], Cot[trkID], len[trkID],
          momentum, firstHit, lastHit
        );
        association->setClusterInfo(
          cluID, Enecl[cluID], Tcl[cluID], clusterPosition
        );
        association->setAssociationInfo(
          ntcl_i, Assleng[ntcl_i], Asschi[ntcl_i], extrapolation
        );
        associationTree->Fill();
      }

      // Iterating over OLD associations
      for(Int_t ntclold_i = 0; ntclold_i<ntclold; ntclold_i++){
        if(ververold[ntclold_i] == 10) { continue; }

        evtID = i;
        runNum = nrun;
        evtNum = nev;

        // associated clutster ID
        Int_t cluID_old = ((Int_t) Assclold[ntclold_i]);

        // Track number (nt) is different than track index (trkind)
        // Asstr[ntcl] has the same value as trkind[nt], iterating over (nt)
        Int_t trkID_old = -1;
        for(Int_t ntold_i = 0; ntold_i<ntold; ntold_i++){
          if(Asstrold[ntclold_i] == trkindold[ntold_i]) { trkID_old = ntold_i; }
        }

        TVector3 extrapolation_old(xextold[ntclold_i], yextold[ntclold_i], zextold[ntclold_i]);
        TLorentzVector momentum_old;
        TVector3 tmpVec_old(pxtold[trkID_old], pytold[trkID_old], pztold[trkID_old]);
        momentum_old.SetVectMag(tmpVec_old, pmodold[trkID_old]);
        TVector3 firstHit_old(xfirstold[trkID_old], yfirstold[trkID_old], zfirstold[trkID_old]);
        TVector3 lastHit_old(xlastold[trkID_old], ylastold[trkID_old], zlastold[trkID_old]);
        TVector3 clusterPosition(Xcl[cluID_old], Ycl[cluID_old], Zcl[cluID_old]);

        association_old = new KAssociation();
        association_old->setTrackInfo(
          trkID_old, trkindold[trkID_old], Curold[trkID_old], Phiold[trkID_old],
          Cotold[trkID_old], lenold[trkID_old], momentum_old, firstHit_old, lastHit_old
        );
        association_old->setClusterInfo(
          cluID_old, Enecl[cluID_old], Tcl[cluID_old], clusterPosition
        );
        association_old->setAssociationInfo(
          ntclold_i, Asslengold[ntclold_i], Asschiold[ntclold_i], extrapolation_old
        );
        associationOldTree->Fill();
      }
    }
  }
  outputFile->Write();
  outputFile->Close();
}
