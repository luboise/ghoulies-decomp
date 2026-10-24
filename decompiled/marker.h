/* marker.h - Spawn/scene markers
   From Ghidra decompilation of Grabbed by the Ghoulies default.xbe. */
#pragma once
#include "common.h"

/* ---- declarations ---- */
extern void Marker::Handler::Handler4(Marker *param_1);
extern void Marker::Handler::Handler3(int param_1);
extern void Marker::Handler::Handler19(int param_1);
extern void Marker::Handler::FxEmitter(int param_1);
extern void Marker::Handler::Handler24(int param_1);
extern void Marker::Handler::Handler11(int param_1);
extern void Marker::Handler::BgBreak(BgBreakMarker *marker);
extern void Marker::Handler::Handler15(Marker *param_1);
extern void Marker::Handler::Handler17(int param_1);
extern void Marker::Handler::Handler16(int param_1);
extern void Marker::Handler::Player(Marker *param_1);
extern void Marker::overridePosAndRot(Marker *param_1,vec3 *param_2,vec3 *param_3);
extern void Marker::Handler::Powerup(Marker *param_1);
extern void Marker::Handler::Handler8(Marker *param_1);
extern void Marker::Handler::Handler20(int param_1);
extern void Marker::Handler::ShockObjectHandler(ScareMarker *param_1);
extern void Marker::Handler::Handler7(int param_1);
extern void Marker::Handler::Handler20(int param_1);
extern void Marker::Handler::ScaleHandler(ScareMarker *this);
extern void Marker::Handler::Handler5(astruct_6 *param_1);
extern Marker * Marker::getMarkerById(uint16_t id);
extern int Marker::getCountOfMarkerType(MarkerType param_1);
extern uint16_t Marker::getFurthestMarkerFromPoint(MarkerType markerType,vec3 *param_2);
extern ushort Marker::nextIdOfNextMarkerOfType(MarkerType markerType,BOOL performFullCheck,short markerId);
extern void Marker::GetPosByIndex(uint16_t markerId,vec3 *outPos);
extern void Marker::getEulersByIndex(uint16_t param_1,vec3 *eulers);
extern uint Marker::GetSmth(uint16_t index);
extern DerivedMarkerValue * Marker::getByID2(uint16_t id2);
