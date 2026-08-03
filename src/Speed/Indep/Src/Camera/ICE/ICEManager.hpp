#ifndef ICEMANAGER_HPP_
#define ICEMANAGER_HPP_

#include "Speed/Indep/Src/Camera/ICE/ICEData.hpp"
#include "Speed/Indep/Src/Ecstasy/Ecstasy.hpp"

struct Matrix4; // TODO where is this from

// File: speed/indep/src/Camera/ICE/ICEManager.hpp
// total size: 0x80
// Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:14
class ICEManager {
  public:
    ICEManager();  // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:17
    ~ICEManager(); // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:18

    bool IsEditorOn() { // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:26
        // TODO maybe negated?
        return nState >= 1;
    }
    bool IsEditorOff() { // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:27
        return nState == 0;
    }

    int GetState() {
        return nState;
    }

    float GetParameter();

    float GetParameterLength() {
        return fParameterLength;
    }

    void Init();                                // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:36
    void Update();                              // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:37
    void Resolve();                             // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:38
    void Render(eView *p_view);                 // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:39
    void LoadCameraSet(bChunk *set_chunk);      // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:40
    void UnloadCameraSet(bChunk *set_chunk);    // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:41
    void LoadCameraShakes(bChunk *set_chunk);   // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:42
    void UnloadCameraShakes(bChunk *set_chunk); // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:43

    struct ICEData *GetCameraData(uint32 scene_hash, int camTrack);
    struct ICEData *GetCameraData(ICETrack **p_track, float *p_start, float *p_end);

    void GetSlope(Vector3 *p_eye_slope, Vector3 *p_look_slope, float *p_dutch_slope, float *p_lens_slope, ICEData *p_camera, int n_key,
                  ICETrack *p_track);

    bool RefreshCameraSplines();

    void FixAnimElevation(Vector3 *position);
    void SetupAnimElevation();
    float GetAnimElevationFixup(Vector3 *position);

    void SetGenericCameraToPlay(const char *group_name, const char *track_name); // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:48
    bool IsGenericCameraPlaying() {}                                             // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:49

    ICEGroup *GetCurrentGroup();
    ICETrack *GetCurrentTrack();
    ICETrack *GetPlaybackTrack() {}
    ICEShakeTrack *GetShakeTrack(uint32 shake_type);
    char *GetShakeTypeName(uint32 shake_type);
    uint32 GetRelativeShakeType(uint32 shake_type, int inc);

    float GetTrackLengthByName(char *trackName);

    void ChooseReplayCamera();        // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:51
    bool ChooseCameraPlaybackTrack(); // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:52
    int GetNumSceneCameraTrack(uint32 scene_hash);
    int GetCameraIndex(float f_param, ICETrack *track);
    void SetSmoothExit(bool smooth) {} // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:53
    bool IsSmoothExit() {}             // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:54
    int ChooseGoodSceneCameraTrackIndex(uint32 scene_hash, Matrix4 *scene_origin);
    void SetUseRealTime(bool val) { // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:55
        bUseRealTime = val;
    }
    float IsUsingRealTime() { // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:56
    }
    float GetTimerSeconds(); // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:57

  private:
    float GetParameter(int i, ICETrack *track);
    float GetIntervalSize(ICEData *data, ICETrack *track);
    float GetIntervalSize(int i);

    ICEData *GetNeighbour(ICEData *data, int key, ICETrack *track);

    ICETrack *ChooseGenericCamera();

    ICEGroup *GetNisCameraGroup(uint32 scene_hash);              // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:65
    ICEGroup *GetFmvCameraGroup(uint32 scene_hash);              // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:66
    ICEGroup *GetReplayCameraGroup(uint32 category_hash);        // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:68
    ICEGroup *GetGenericCameraGroup(uint32 name_hash);           // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:69
    ICEGroup *AddCameraGroup(ICEContext context, uint32 handle); // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:62
    ICEGroup *GetCameraGroup(ICEContext context, uint32 handle); // Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:63

    int GetNumGroupsWithData(ICEContext context);
    int GetNumGroups();
    int GetNumTracks();

    ICEGroup *pNisCameras;          // offset 0x0, size 0x4
    ICEGroup *pFmvCameras;          // offset 0x4, size 0x4
    ICEGroup *pReplayCameras;       // offset 0x8, size 0x4
    ICEGroup *pGenericCameras;      // offset 0xC, size 0x4
    ICEShakeGroup *pShakeGroup;     // offset 0x10, size 0x4
    int nNisCameras;                // offset 0x14, size 0x4
    int nFmvCameras;                // offset 0x18, size 0x4
    int nReplayCameras;             // offset 0x1C, size 0x4
    int nGenericCameras;            // offset 0x20, size 0x4
    ICETrack *pPlaybackTrack;       // offset 0x24, size 0x4
    int nState;                     // offset 0x28, size 0x4
    int nTrack;                     // offset 0x2C, size 0x4
    int nHandle;                    // offset 0x30, size 0x4
    int nOption;                    // offset 0x34, size 0x4
    int nSetting;                   // offset 0x38, size 0x4
    int nExitConfirmOption;         // offset 0x3C, size 0x4
    int nDeleteConfirmOption;       // offset 0x40, size 0x4
    int nContext;                   // offset 0x44, size 0x4
    int nCopyMode;                  // offset 0x48, size 0x4
    uint32 nSceneHash;              // offset 0x4C, size 0x4
    float fAnimElevation;           // offset 0x50, size 0x4
    float fParameterStart;          // offset 0x54, size 0x4
    float fParameterLength;         // offset 0x58, size 0x4
    float fParameterLengthBackup;   // offset 0x5C, size 0x4
    char nPlayGenericTrackName[14]; // offset 0x64, size 0xE
    int nMarkerIndex;               // offset 0x78, size 0x4
    bool bUseRealTime;              // offset 0x7C, size 0x1
    uint32 nPlayGenericGroupHash;   // offset 0x60, size 0x4, Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:83
    bool bSmoothExit;               // offset 0x74, size 0x1, Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:85
};

ICEManager TheICEManager; // size: 0x80, Decl: speed/indep/src/Camera/ICE/ICEManager.hpp:93

void ICECompleteEventTags();

#endif
