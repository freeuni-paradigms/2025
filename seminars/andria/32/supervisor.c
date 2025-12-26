#include "supervisor.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void RandSleep() {
  sleep(rand() % 5);
}

void HardwareWorkerEnterRoom(int hardware_member_id) {
  RandSleep();
  printf("Hardware crew member entered room: %d\n", hardware_member_id);
}

void HardwareWorkerStartSettingUpComputer(int hardware_member_id, int table_id) {
  RandSleep();
  printf("Hardware crew member started setting up computer on table: %d %d\n", hardware_member_id, table_id);
}

void HardwareWorkerFinishedSettingUpComputer(int hardware_member_id, int table_id) {
  RandSleep();
  printf("Hardware crew member finished setting up computer on table: %d %d\n", hardware_member_id, table_id);
}

void HardwareWorkerLeaveRoom(int hardware_member_id) {
  RandSleep();
  printf("Hardware crew member left room: %d\n", hardware_member_id);
}

void AllComputerHardwareIsSetUp(int hardware_member_id) {
  RandSleep();
  printf("All computer hardware is set up: %d\n", hardware_member_id);
}

void SoftwareWorkerEnterRoom(int software_member_id) {
  RandSleep();
  printf("Software crew member entered room: %d\n", software_member_id);
}

void SoftwareWorkerStartInstallingSoftware(int software_member_id, int computer_id) {
  RandSleep();
  printf("Software crew member is installing software on computer: %d %d\n", software_member_id, computer_id);
}

void SoftwareWorkerFinishedInstallingSoftware(int software_member_id, int computer_id) {
  RandSleep();
  printf("Software crew member finished installing software on computer: %d %d\n", software_member_id, computer_id);
}

void SoftwareWorkerLeaveRoom(int software_member_id) {
  RandSleep();
  printf("Software crew member left room: %d\n", software_member_id);
}

void AllComputerSoftwareIsInstalled(int software_member_id) {
  RandSleep();
  printf("All computer software is set up: %d\n", software_member_id);  
}
