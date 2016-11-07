#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <stdlib.h>

using namespace std;

struct arpPacket{
  string option; // replay (2) or request (1)
  string sMac;
  string sIp;
};

const int THRESHOLD = 5; //enough number of arp replays to consider an attack
map<string, int> macMapper;
map<string, int> ipMapper;
arpPacket atacante; // holds answers of attacker
arpPacket victima; //holds answers of victim

string findMacOfSpoofer() { // da fuck
    map<string, int>::iterator it = macMapper.begin();
    for (it = macMapper.begin(); it != macMapper.end(); it++) {
        if (it->second > THRESHOLD) {
            //cout << "Mac of spoofer: " << it->first << endl;
              return it->first; //returns mac of spoofer
        }
    }
    return "no spoofing"; //in case of a NO spoof, should not happen
}

string findMacOfVictim(vector<arpPacket> packets) {
  for (int i = 0; i < packets.size(); i++) {
    if(packets[i].sIp == victima.sIp) {
      if (packets[i].sMac != atacante.sMac) {
        return packets[i].sMac;
      }
    }
  }
  return "Victim mac not found";
}


/*
 * Finds IP's from attacker and victim
 * Saves them in corresponding packets
*/
void findIPs(string sMacOfSpoofer, vector<arpPacket> packets) {
  map<string, int>::iterator it = ipMapper.begin();
  int iCont = 0;
  string matiPs[2][2]; //array of IP's with the respective count

  //meter al mapa
  for(int i = 0; i < packets.size(); i++) {
      if(packets[i].sMac == sMacOfSpoofer) {
          ipMapper[packets[i].sIp]++;
      }
  }

  for (it = ipMapper.begin(); it != ipMapper.end(); it++) {
      //cout << it->first << "->" << it->second << endl;
      matiPs[iCont][0] = it->first;
      matiPs[iCont][1] = it->second;
      iCont++;
  }

  //Assigns corresponding IP to attacker and victim
  if(matiPs[0][1] > matiPs[1][1] ) {
      //cout << "IP of victim " << matiPs[0][0] << endl;
      victima.sIp = matiPs[0][0];
      //cout << "IP of attacker " << matiPs[1][0] << endl;
      atacante.sIp = matiPs[1][0];
  }
  else {
      //cout << "IP of victim " << matiPs[1][0] << endl;
      victima.sIp = matiPs[1][0];
      //cout << "IP of attacker " << matiPs[0][0] << endl;
      atacante.sIp = matiPs[0][0];
  }
}

void insertIntoMap(string mac) {
  macMapper[mac] = 0;
}

//keeps delta of replays and requests
int optionDirfference(vector<arpPacket> packets) {
  //no asegura que alguien este haciendo poisioning
  int option = 0;

  for (int i = 0; i < packets.size(); i++) {
    if (packets[i].option == "2") {
      option++;
      macMapper[packets[i].sMac]++;
    }
    if (packets[i].option == "1") {
      option--;
      macMapper[packets[i].sMac]--;
    }
  }

  return option;
}

bool isSpoofing (vector<arpPacket> packets) {
  return optionDirfference(packets) >= THRESHOLD;
}

// Write packets to file
vector<arpPacket> writePacketstoFile() {
  vector<arpPacket> packets;
  ifstream myFile;

  myFile.open("arp.txt");
  string sOption;
  string sMac;
  string sIp;
  arpPacket op2Packet;
  arpPacket op1Packet;

  while (myFile >> sOption >> sMac >> sIp) {
    insertIntoMap(sMac);
    if(sOption == "1") {
      op1Packet.option = sOption;
      op1Packet.sIp = sIp;
      packets.push_back(op1Packet);
    }
    else {
      op2Packet.option = sOption;
      op2Packet.sMac = sMac;
      op2Packet.sIp = sIp;
      packets.push_back(op2Packet);
    }
  }

  myFile.close();
  return packets;
}

void printAnswer(arpPacket victima, arpPacket atacante){
    cout << "Mac of victim:    " << victima.sMac << endl;
    cout << "Mac of attacker:  " << atacante.sMac << endl;
    cout << "IP of victim:     " << victima.sIp << endl;
    cout << "IP of attacker:   " << atacante.sIp << endl;
    string victimCommand = "python macOfVictim.py " + victima.sIp;
    system(victimCommand.c_str());
}

int main() {
  vector<arpPacket> packets;
  packets = writePacketstoFile();

  if(isSpoofing(packets)) {
      atacante.sMac = findMacOfSpoofer();
      findIPs(atacante.sMac, packets);
      victima.sMac = findMacOfVictim(packets);
      printAnswer(victima, atacante);
  }
  else {
      cout << "Do not worry, be happy" << endl;
  }

}
