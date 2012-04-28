#ifndef INPUTTASK_H_
#define INPUTTASK_H_

class InputScene;
///////////////////////////////////////////////////////////////////////////////
/// <summary>
///   <c>InputTask</c> Implementation of the ISystemTask interface for Input.
/// </summary>
///////////////////////////////////////////////////////////////////////////////

class InputTask : public ISystemTask
{
	friend class InputScene;
protected:
	InputTask( InputScene* _pScene );
	~InputTask( void );

	/// <summary cref="InputTask::GetSystemType">
	///   Implementation of the <c>ISystemTask::GetSystemType</c> function.
	///   Gets the system type for this system task.
	/// </summary>
	/// <returns>System::Type - The type of the system.</returns>
	/// <seealso cref="ISystemTask::GetSystemType"/>
	virtual System::Type GetSystemType( void );

	/// <summary cref="InputTask::Update">
	///   Implementation of the <c>ISystemTask::Update</c> function.
	///   Function informing the task to perform its updates.  This does
	///   all the work needed to update Input objects for this frame.
	/// </summary>
	/// <param name="DeltaTime">The time delta from the last call.</param>
	/// <seealso cref="ISystemTask::Update"/>
	virtual void Update( f32 DeltaTime );

	/// <summary cref="InputTask::IsPrimaryThreadOnly">
	///   Implementation of the <c>ISystemTask::IsPrimaryThreadOnly</c> function.
	/// </summary>
	/// <returns>Bool - Returns true if this system should only run on the primary thread.</returns>
	/// <seealso cref="ISystemTask::IsPrimaryThreadOnly"/>
	virtual Bool IsPrimaryThreadOnly( void ) { return true; } 

private:
	InputScene*                     pScene;
};

#endif //INPUTTASK_H_