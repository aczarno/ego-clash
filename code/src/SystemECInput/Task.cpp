//
// extern includes
//
#include <windows.h>

//
// core includes
//
#include "..\BaseTypes\BaseTypes.h"
#include "..\Interfaces\Interface.h"

//
// system includes
//
#include "Scene.h"
#include "Object.h"
#include "Task.h"

InputTask::InputTask(InputScene* _pScene) : ISystemTask(_pScene), pScene(_pScene)
{
	ASSERT(pScene != NULL);
	ASSERT(sizeof(LONG) == sizeof(i32));
}

InputTask::~InputTask( void )
{
}

System::Type InputTask::GetSystemType( void )
{
	return System::Types::Input;
}

void InputTask::Update( f32 DeltaTime )
{
	pScene->InputUpdate(DeltaTime);
}