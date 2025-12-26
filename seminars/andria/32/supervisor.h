#ifndef PARADIGMS_PROBLEMS_THREADS_SERVER_ROOM_SUPERVISOR_H_
#define PARADIGMS_PROBLEMS_THREADS_SERVER_ROOM_SUPERVISOR_H_

void HardwareWorkerEnterRoom(int hardware_member_id);
void HardwareWorkerStartSettingUpComputer(int hardware_member_id, int table_id);
void HardwareWorkerFinishedSettingUpComputer(int hardware_member_id, int table_id);
void HardwareWorkerLeaveRoom(int hardware_member_id);

// Last hardware crew member leaving room should call this before leaving room.
void AllComputerHardwareIsSetUp(int hardware_member_id);

void SoftwareWorkerEnterRoom(int software_member_id);
void SoftwareWorkerStartInstallingSoftware(int software_member_id, int computer_id);
void SoftwareWorkerFinishedInstallingSoftware(int software_member_id, int computer_id);
void SoftwareWorkerLeaveRoom(int software_member_id);

// Last software crew member leaving room should call this before leaving room.
void AllComputerSoftwareIsInstalled(int software_member_id);

#endif // PARADIGMS_PROBLEMS_THREADS_SERVER_ROOM_SUPERVISOR_H_
