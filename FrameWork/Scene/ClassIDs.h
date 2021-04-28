#pragma once

#define ClassID(x) CLASS_##x
#define DefineClassID(x, classID) ClassID(x) = classID

// Runtime classIDs are kept intentionally small.
enum ClassIDType
{
    DefineClassID(Undefined, -1),
    DefineClassID(Renderer, 2),
    DefineClassID(MeshDatas, 3),
    DefineClassID(Transform, 5),
    DefineClassID(Camera, 6),
    DefineClassID(Light, 7),
    DefineClassID(CanvasRenderer, 8),
    DefineClassID(Widget, 9),
    DefineClassID(PointLight, 10),
    DefineClassID(AreaLight, 11),
    DefineClassID(SpotLight, 12),
    DefineClassID(DirectionalLight, 13),
    DefineClassID(Cube, 14),
};

//make sure people dont accidentally define classids in other files:
#undef DefineClassID
