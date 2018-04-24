/*
 * Sauviz Fardad
 * sxf160430@utdallas.edu
 * CS 3377.501
 */

#include <stdio.h>
#include <fstream>
#include <stdint.h>
#include "cdk.h"

#define BUFFERSIZE 100

using namespace std;

// Used to hold the header information
class BinaryFileHeader
{ 
public:
  uint32_t magicNumber;         
  uint32_t versionNumber;
  uint64_t numRecords;
};  

const int maxRecordStringLength = 25;

//used to hold the information of each record
class BinaryFileRecord
{ 
public:
  uint8_t strLength;
  char  stringBuffer[maxRecordStringLength];
};  


void printMatrix(CDKMATRIX *matrix)
{
  BinaryFileHeader *header = new BinaryFileHeader;
  
  BinaryFileRecord *record = new BinaryFileRecord;
  
  ifstream fs("cs3377.bin", ios::binary | ios::in);

  char temp[BUFFERSIZE]; //used to store strings
  
  fs.read( (char *) header, sizeof(BinaryFileHeader)); //reads the entire header
  
  snprintf(temp, BUFFERSIZE, "Magic: 0x%X",   header->magicNumber); 
  
  setCDKMatrixCell(matrix, 1, 1, temp); //prints string into matrix cell
  
  snprintf(temp, BUFFERSIZE, "Version: %u", header->versionNumber);
  
  setCDKMatrixCell(matrix, 1, 2, temp); //prints tring into matrix cell
  
  snprintf(temp, BUFFERSIZE, "NumRecords: %lu", header->numRecords);
  
  setCDKMatrixCell(matrix, 1, 3, temp); 
  
  //loops through and prints each record in the file
  for(int i = 1; i <= (int) header->numRecords; i++)
    {
      fs.read((char*) record, sizeof(BinaryFileRecord));
      snprintf(temp, BUFFERSIZE, "strLength: %u", record->strLength);
      setCDKMatrixCell(matrix, i+1, 1, temp);
      setCDKMatrixCell(matrix, i+1, 2, record->stringBuffer); 
    }
  
  //deletes dynamically allocated memory
  delete header;
  delete record;

  //closes file
  fs.close();
}
