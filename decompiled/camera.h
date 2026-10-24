/* camera.h - Camera configs and management (playcam/director)
   From Ghidra decompilation of Grabbed by the Ghoulies default.xbe. */
#pragma once
#include "common.h"

/* ---- declarations ---- */
extern void GamePauseContext::loadShaderPages(BOOL gpc,GamePauseContext *param_2);
extern GamePauseContext * GamePauseContext::ctor(uint id,uint param_2,char *name);
extern void __fastcall Camera::AppendAndSelect(Camera *proj,uint index);
extern void Camera::setActiveCamera(Camera *cam);
extern BOOL Camera::SetActiveCameraConfig(uint cameraIndex,char *name);
extern void Camera::RevertCameraUsingConfig(Camera *config);
extern float __fastcall Camera::ctor(Camera *mv,char *name,ProjectionSetBitField flags);
extern AspectRatioType CameraDescriptor::interpolateVal9(CameraDescriptor *param_1,float t);
