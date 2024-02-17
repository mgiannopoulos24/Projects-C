#include <stdio.h>
#define MODE 4 //Definition to use each mode 
#ifdef WIN32
#include <io.h>
#include <fcntl.h>
#endif


int sof;                //Size of file       
int sfc;                //Size of Format Data
short wvfmt=1;          //Wave Format
short mnstr;            //Mono / Stereo
int samplert;           //Sample Rate
int bps;                //Bytes per second
short blockal;          //Block alignment
short bitps;            //Bit per second
int sod;                //Size of data chunk
long data_count;        //Data 

int main(void)
{
    #ifdef WIN32
    _setmode (_fileno (stdout), O_BINARY);
    _setmode (_fileno (stdin), O_BINARY);
    #endif

    if (MODE == 1)  
    {
        int c1,c2,c3,c4; //Variables one byte each to read the characters from wav files
       
        
        c1=getchar(); //RIFF Check
        c2=getchar(); //
        c3=getchar(); //
        c4=getchar(); //
            
        if (c1!=82 || c2!=73 || c3!=70 || c4!=70)           //If c1-c4 characters differ from ASCII code letters "R I F F", print error message and terminate the program
        {
            fprintf(stderr,"Error! \"RIFF\" not found\n");  
            return 0;
        }


        c1=getchar(); //Size of file
        c2=getchar(); // 
        c3=getchar(); // 
        c4=getchar(); //

        sof=c4*256*256*256+c3*256*256+c2*256+c1;//Type to calculate Size of file 
        
        fprintf(stderr,"Size of file: %d \n",sof); //Print size of file

        

        c1=getchar(); //WAVE check
        c2=getchar(); //
        c3=getchar(); //
        c4=getchar(); //

        

        if (c1!=87 || c2!=65 || c3!=86 || c4!=69)        //If c1-c4 characters differ from ASCII code letters "W A V E", print error message and terminate the program
        {         
            fprintf(stderr,"Error! \"WAVE\" not found.\n"); 
            return 0;
        }

        

        c1=getchar(); //"fmt "check
        c2=getchar(); //
        c3=getchar(); //
        c4=getchar(); //

        if (c1!=102|| c2!=109 || c3!=116||c4!=32)
        {
            fprintf(stderr,"Error! \"fmt \" not found\n");   //If c1-c4 characters differ from ASCII code letters "f m t (space)", print error message and terminate the program
            return 0;
        }

        c1=getchar(); //format
        c2=getchar(); //
        c3=getchar(); //
        c4=getchar(); //

        sfc=c4*256*256*256+c3*256*256+c2*256+c1; //Type to calculate Size of format chunk
        fprintf(stderr,"Size of format chunk: %d\n",sfc); //Print size of format chunk
    
        c1=getchar(); //Type of WAVE format
        c2=getchar(); //

        wvfmt=c2*256+c1;
        fprintf(stderr,"Type of WAVE format: %d\n",wvfmt); 
        if (wvfmt!=1)                       //If wvfmt(wave format) variable is different than number 1, print error message and terminate the program
        {
            fprintf(stderr,"Error! WAVE type format should be 1\n");
            return 0;
        }
        
        c1=getchar(); //Mono or stereo 
        c2=getchar(); //

        mnstr=c2*256+c1; 
        fprintf(stderr,"mono/stereo: %d \n",mnstr);            //If mnstr(mono/stereo) variable is different than number 1 or 2,print error message and terminate the program
        if (mnstr!=1 && mnstr!=2)
        {
            fprintf(stderr,"Error! mono/stereo should be 1 or 2\n");
            return 0;
        }
       

        c1=getchar(); //Sample rate
        c2=getchar(); //
        c3=getchar(); //
        c4=getchar(); //


        samplert=c4*256*256*256+c3*256*256+c2*256+c1;     //Type to calculate Sample rate
        fprintf(stderr,"Sample rate: %d\n",samplert);   //Print sample rate

        c1=getchar(); //Bytes per second
        c2=getchar(); //
        c3=getchar(); //
        c4=getchar(); //

        bps=c4*256*256*256+c3*256*256+c2*256+c1;  //Type to calculate Bytes per second 
        fprintf(stderr,"Bytes/sec: %d\n",bps); //Print bytes per second
        


        c1=getchar(); //Block alignment
        c2=getchar(); //


        blockal=c2*256+c1;  //Type to calculate Block alignment
        fprintf(stderr,"Block alignment: %d\n",blockal);  //Print block alignment

        
        if (bps!=samplert*blockal)                       //If bps variable (bytes per second) doesnt equal to the product of sample rate multiplied by block alignment times, print error message and terminate the program
        {
            fprintf(stderr,"Error! bytes/second should be sample rate x block alignment \n");
            return 0;
        }
        
        
        c1=getchar(); //Bits per second
        c2=getchar(); //

        bitps=c2*256+c1;//Type to calculate Bits per second
        fprintf(stderr,"Bits per sample: %d \n",bitps); //Print bits per sample
      
                

 
        if (bitps!=8 && bitps!=16)             //If bitps  variable (bits per second) is different than number 8 or number 16, print error message and terminate the program
        {
            fprintf(stderr,"Error! bits/sample should be 8 or 16 \n");
            return 0;
        }

        if (blockal!=(bitps/8)*mnstr)           //If blockal variable (blockalignment) doesnt equal to the product of bits per second variable divided by 2 and after multiplies by mono/stereo times, print error message and terminate the program
        {  
            fprintf(stderr,"Error! block alignment should be bits per sample / 8 x mono/stereo\n");
            return 0;
        }
        

        c1=getchar(); //Start of data
        c2=getchar(); //
        c3=getchar(); //
        c4=getchar(); //

        if (c1!=100 || c2!=97 || c3!=116 ||c4!=97)               //If c1-c4 characters differ from ASCII code letters "d a t a", print error message and terminate the program
        {
            fprintf(stderr,"Error! \"data\" not found");
            return 0;
        }

       
        c1=getchar(); //Size of data chunk
        c2=getchar(); //
        c3=getchar(); //
        c4=getchar(); //

        sod=c4*256*256*256+c3*256*256+c2*256+c1;  //Type to calculate size of data
        fprintf(stderr,"Size of data chunk: %d\n",sod); //Print size of data

   
        data_count=8+sfc+12; //Data count is equal to 4 bytes for "WAVE" + 4 bytes for "fmt "+ 4 bytes for the size of format chunk+ 4 bytes for size of format chunck filed + 4 bytes for Size of data
        while ((c1 = getchar()) != EOF) //Get every character left until end of file
        data_count++;      //Add every byte left until end of file
               
        if (data_count < sof)      //If data_count is lower than size of file, print error message and terminate the program
        {
            fprintf(stderr,"Error! insufficient data.\n");
            return 0;
        }
        if (data_count > sof)      //If data_count is higher than size of file, print error message and terminate the program
        {
            fprintf(stderr,"Error! bad file size.\n");
            return 0;
        }
     
        
    }

    if (MODE==2)
    {
        int c1,c2,c3,c4; //Variables one byte each to read the characters from wav files
        int temp_samplert,temp_bps; //Variables for the new sample rate and new bytes per second.
        
        c1=getchar(); //RIFF Check
        c2=getchar(); //
        c3=getchar(); //
        c4=getchar(); //

        
        if (c1!=82 || c2!=73 || c3!=70 || c4!=70)           //If c1-c4 characters differ from ASCII code letters "R I F F", print error message and terminate the program
        {
            fprintf(stderr,"Error! \"RIFF\" not found\n");  
            return 0;
        }

        putchar(c1); //Place the character on the new file
        putchar(c2); //Place the character on the new file
        putchar(c3); //Place the character on the new file
        putchar(c4); //Place the character on the new file    

        c1=getchar(); //Size of file
        c2=getchar(); // 
        c3=getchar(); // 
        c4=getchar(); //


        

        sof=c4*256*256*256+c3*256*256+c2*256+c1;//Type to calculate Size of file 
        
        fprintf(stderr,"Size of file: %3d \n",sof); //Print size of file

        putchar(c1); //Place the character on the new file
        putchar(c2); //Place the character on the new file
        putchar(c3); //Place the character on the new file
        putchar(c4); //Place the character on the new file


        c1=getchar(); //WAVE check
        c2=getchar(); //
        c3=getchar(); //
        c4=getchar(); //

        
        

        if (c1!=87 || c2!=65 || c3!=86 || c4!=69)        //If c1-c4 characters differ from ASCII code letters "W A V E", print error message and terminate the program
        {         
            fprintf(stderr,"Error! \"WAVE\" not found.\n");
            return 0;
        }

        putchar(c1); //Place the character on the new file
        putchar(c2); //Place the character on the new file
        putchar(c3); //Place the character on the new file
        putchar(c4); //Place the character on the new file


        c1=getchar(); //"fmt "check
        c2=getchar(); //
        c3=getchar(); //
        c4=getchar(); //

       
        if (c1!=102|| c2!=109 || c3!=116||c4!=32)
        {
            fprintf(stderr,"Error! \"fmt \" not found\n");   //If c1-c4 characters differ from ASCII code letters "f m t (space)", print error message and terminate the program
            return 0;
        }

        putchar(c1); //Place the character on the new file
        putchar(c2); //Place the character on the new file
        putchar(c3); //Place the character on the new file
        putchar(c4); //Place the character on the new file
        
        

        c1=getchar(); //format
        c2=getchar(); //
        c3=getchar(); //
        c4=getchar(); //

        

        sfc=c4*256*256*256+c3*256*256+c2*256+c1; //Type to calculate the size of format chunk
        fprintf(stderr,"Size of format chunk: %d\n",sfc); //Print the size of format chunk

        putchar(c1); //Place the character on the new file
        putchar(c2); //Place the character on the new file
        putchar(c3); //Place the character on the new file
        putchar(c4); //Place the character on the new file

        c1=getchar(); //Type of WAVE format
        c2=getchar(); //

        

        wvfmt=c2*256+c1;//Type to calculate wave format
        fprintf(stderr,"Type of WAVE format: %d\n",wvfmt); 
        if (wvfmt!=1)                                      //If wvfmt(wave format) variable is different than number 1, print error message and terminate the program
        {
            fprintf(stderr,"Error! WAVE type format should be 1\n");
            return 0;
        }

        putchar(c1); //Place the character on the new file
        putchar(c2); //Place the character on the new file

        c1=getchar(); //Mono or stereo 
        c2=getchar(); //

        
    
        mnstr=c2*256+c1; //Type to calculate mono or stereo
        
        fprintf(stderr,"mono/stereo: %d \n",mnstr);            //If mnstr(mono/stereo) variable is different than number 1 or 2,print error message and terminate the program
        
        if (mnstr!=1 && mnstr!=2)
        {
            fprintf(stderr,"Error! mono/stereo should be 1 or 2\n");
            return 0;
        }
       
        putchar(c1); //Place the character on the new file
        putchar(c2); //Place the character on the new file

        c1=getchar(); //Sample rate
        c2=getchar(); //
        c3=getchar(); //
        c4=getchar(); //

        

        samplert=c4*256*256*256+c3*256*256+c2*256+c1;     //Type to calculate Sample rate
        fprintf(stderr,"Sample rate: %d\n",samplert);   //Print sample rate

        temp_samplert=samplert/2; //We need half speed on the new file so we have to divide the current sample rate by 2

        c4=temp_samplert/(256*256*256); //Type to calculate the new character to place in the new file created
        temp_samplert=temp_samplert - c4*256*256*256; //Substract the above character from the new sample rate
        c3=temp_samplert/(256*256); //Type to calculate the new character to place in the new file created
        temp_samplert=temp_samplert - c3*256*256; //Substract the above character from the new sample rate
        c2=temp_samplert/256; //Type to calculate the new character to place in the new file created
        c1=temp_samplert-(c2*256); //Type to calculate the new character to place in the new file created
        
        putchar(c1); //Place the character on the new file
        putchar(c2); //Place the character on the new file
        putchar(c3); //Place the character on the new file
        putchar(c4); //Place the character on the new file
        

        c1=getchar(); //Bytes per second
        c2=getchar(); //
        c3=getchar(); //
        c4=getchar(); //

        
        bps=c4*256*256*256+c3*256*256+c2*256+c1;  //Type to calculate Bytes per second 
        fprintf(stderr,"Bytes/sec: %d\n",bps); //Print bytes per second
        

        temp_bps=bps/2; //We need half speed on the new file so we also have to divide the current bytes per second by 2
        fprintf(stderr,"temp_bytes/sec: %d\n",temp_bps); //Print bytes per second

                       
        c4=temp_bps/(256*256*256); //Type to calculate the new character to place in the new file created
        temp_bps=temp_bps-c4*256*256*256; //Substract the above character from the new bytes per second
        c3=temp_bps/(256*256); //Type to calculate the new character to place in the new file created
        temp_bps=temp_bps-c3*256*256; //Substract the above character from the new bytes per second
        c2=temp_bps/256; //Type to calculate the new character to place in the new file created
        c1=temp_bps-(c2*256); //Type to calculate the new character to place in the new file created

        putchar(c1); //Place the character on the new file
        putchar(c2); //Place the character on the new file
        putchar(c3); //Place the character on the new file
        putchar(c4); //Place the character on the new file

        c1=getchar(); //Block alignment
        c2=getchar(); //

        

        blockal=c2*256+c1;  //Type to calculate Block alignment
        fprintf(stderr,"Block alignment: %d\n",blockal);  //Print block alignment

        putchar(c1); //Place the character on the new file
        putchar(c2); //Place the character on the new file

        if (bps!=samplert*blockal)                       //If bps variable (bytes per second) doesnt equal to the product of sample rate multiplied by block alignment times, print error message and terminate the program
        {
            fprintf(stderr,"Error! bytes/second should be sample rate x block alignment \n");
            return 0;
        }
        
        

        
        c1=getchar(); //Bits per second
        c2=getchar(); //

        
        

        bitps=c2*256+c1;//Type to calculate Bits per second
        fprintf(stderr,"Bits per sample: %d \n",bitps);   //Print bits per second
        
        
 
        if (bitps!=8 && bitps!=16)             //If bitps  variable (bits per second) is different than number 8 or number 16, print error message and terminate the program
        {
            fprintf(stderr,"Error! bits/sample should be 8 or 16 \n");
            return 0;
        }

        if (blockal!=(bitps/8)*mnstr)           //If blockal variable (blockalignment) doesnt equal to the product of bits per second variable divided by 2 and after multiplies by mono/stereo times, print error message and terminate the program
        {  
            fprintf(stderr,"Error! block alignment should be bits per sample / 8 x mono/stereo\n");
            return 0;
        }
        
        putchar(c1); //Place the character on the new file
        putchar(c2); //Place the character on the new file

        c1=getchar(); //Start of data
        c2=getchar(); //
        c3=getchar(); //
        c4=getchar(); //

        
        if (c1!=100 || c2!=97 || c3!=116 ||c4!=97)               //If c1-c4 characters differ from ASCII code letters "d a t a", print error message and terminate the program
        {
            fprintf(stderr,"Error! \"data\" not found");
            return 0;
        }

        putchar(c1); //Place the character on the new file
        putchar(c2); //Place the character on the new file
        putchar(c3); //Place the character on the new file
        putchar(c4); //Place the character on the new file

       
        c1=getchar(); //Size of data chunk
        c2=getchar(); //
        c3=getchar(); //
        c4=getchar(); //

        

        sod=c4*256*256*256+c3*256*256+c2*256+c1;  //Type to calculate size of data
        fprintf(stderr,"Size of data chunk: %d\n",sod); //Print size of data

        putchar(c1); //Place the character on the new file
        putchar(c2); //Place the character on the new file
        putchar(c3); //Place the character on the new file
        putchar(c4); //Place the character on the new file
    
        data_count=8+sfc+12; //Data count is equal to 4 bytes for "WAVE" + 4 bytes for "fmt "+ 4 bytes for the size of format chunk+ 4 bytes for size of format chunck filed + 4 bytes for Size of data
        while ((c1 = getchar()) != EOF) //Get every character left until end of file
        {
            data_count++; //Add every byte left until end of file
            putchar(c1);  //And place every character until end of file to the new file created  
        }
        if (data_count < sof)      //If data_count is lower than size of file, print error message and terminate the program
        {
            fprintf(stderr,"Error! insufficient data.\n");
            return 0;
        }
        if (data_count > sof)      //If data_count is higher than size of file, print error message and terminate the program
        {
            fprintf(stderr,"Error! bad file size.\n");
            return 0;
        }
    }

    if (MODE==3)
    {
        int c1,c2,c3,c4; //Variables one byte each to read the characters from wav files
        int temp_samplert,temp_bps; //Variables for the new sample rate and new bytes per second.
        
        c1=getchar(); //RIFF Check
        c2=getchar(); //
        c3=getchar(); //
        c4=getchar(); //

        
        if (c1!=82 || c2!=73 || c3!=70 || c4!=70)           //If c1-c4 characters differ from ASCII code letters "R I F F", print error message and terminate the program
        {
            fprintf(stderr,"Error! \"RIFF\" not found\n");  
            return 0;
        }

        putchar(c1); //Place the character on the new file
        putchar(c2); //Place the character on the new file
        putchar(c3); //Place the character on the new file
        putchar(c4); //Place the character on the new file    

        c1=getchar(); //Size of file
        c2=getchar(); // 
        c3=getchar(); // 
        c4=getchar(); //


        

        sof=c4*256*256*256+c3*256*256+c2*256+c1;//Type to calculate Size of file 
        
        fprintf(stderr,"Size of file: %3d \n",sof); //Print size of file

        putchar(c1); //Place the character on the new file
        putchar(c2); //Place the character on the new file
        putchar(c3); //Place the character on the new file
        putchar(c4); //Place the character on the new file


        c1=getchar(); //WAVE check
        c2=getchar(); //
        c3=getchar(); //
        c4=getchar(); //

        
        

        if (c1!=87 || c2!=65 || c3!=86 || c4!=69)        //If c1-c4 characters differ from ASCII code letters "W A V E", print error message and terminate the program
        {         
            fprintf(stderr,"Error! \"WAVE\" not found.\n");
            return 0;
        }

        putchar(c1); //Place the character on the new file
        putchar(c2); //Place the character on the new file
        putchar(c3); //Place the character on the new file
        putchar(c4); //Place the character on the new file


        c1=getchar(); //"fmt "check
        c2=getchar(); //
        c3=getchar(); //
        c4=getchar(); //

       
        if (c1!=102|| c2!=109 || c3!=116||c4!=32)
        {
            fprintf(stderr,"Error! \"fmt \" not found\n");   //If c1-c4 characters differ from ASCII code letters "f m t (space)", print error message and terminate the program
            return 0;
        }

        putchar(c1); //Place the character on the new file
        putchar(c2); //Place the character on the new file
        putchar(c3); //Place the character on the new file
        putchar(c4); //Place the character on the new file
        
        

        c1=getchar(); //format
        c2=getchar(); //
        c3=getchar(); //
        c4=getchar(); //

        

        sfc=c4*256*256*256+c3*256*256+c2*256+c1; //Type to calculate size of file chunk
        fprintf(stderr,"Size of format chunk: %d\n",sfc); //Print size of file chunk

        putchar(c1); //Place the character on the new file
        putchar(c2); //Place the character on the new file
        putchar(c3); //Place the character on the new file
        putchar(c4); //Place the character on the new file

        c1=getchar(); //Type of WAVE format
        c2=getchar(); //

        

        wvfmt=c2*256+c1; //Type to calculate wave format
        fprintf(stderr,"Type of WAVE format: %d\n",wvfmt); 
        if (wvfmt!=1)                                      //If wvfmt(wave format) variable is different than number 1, print error message and terminate the program
        {
            fprintf(stderr,"Error! WAVE type format should be 1\n");
            return 0;
        }

        putchar(c1); //Place the character on the new file
        putchar(c2); //Place the character on the new file

        c1=getchar(); //Mono or stereo 
        c2=getchar(); //

        
    
        mnstr=c2*256+c1; //Type to calculate mono or stereo
        
        fprintf(stderr,"mono/stereo: %d \n",mnstr);            //If mnstr(mono/stereo) variable is different than number 1 or 2,print error message and terminate the program
        
        if (mnstr!=1 && mnstr!=2)
        {
            fprintf(stderr,"Error! mono/stereo should be 1 or 2\n");
            return 0;
        }
       
        putchar(c1); //Place the character on the new file
        putchar(c2); //Place the character on the new file

        c1=getchar(); //Sample rate
        c2=getchar(); //
        c3=getchar(); //
        c4=getchar(); //

        

        samplert=c4*256*256*256+c3*256*256+c2*256+c1;     //Type to calculate Sample rate
        fprintf(stderr,"Sample rate: %d\n",samplert);  //Print sample rate

        temp_samplert=samplert*2; //We need double speed on the new file so we have to multiply the current sample rate by 2
        //fprintf(stderr,"temp_sample rate: %d \n",temp_samplert);

        c4=temp_samplert/(256*256*256); //Type to calculate the new character to place in the new file created
        temp_samplert=temp_samplert - c4*256*256*256; //Substract the above character from the new sample rate
        c3=temp_samplert/(256*256); //Type to calculate the new character to place in the new file created
        temp_samplert=temp_samplert - c3*256*256; //Substract the above character from the new sample rate
        c2=temp_samplert/256; //Type to calculate the new character to place in the new file created
        c1=temp_samplert-(c2*256); //Type to calculate the new character to place in the new file created
        
        putchar(c1); //Place the character on the new file
        putchar(c2); //Place the character on the new file
        putchar(c3); //Place the character on the new file
        putchar(c4); //Place the character on the new file
        

        c1=getchar(); //Bytes per second
        c2=getchar(); //
        c3=getchar(); //
        c4=getchar(); //

        
        bps=c4*256*256*256+c3*256*256+c2*256+c1;  //Type to calculate Bytes per second 
        fprintf(stderr,"Bytes/sec: %d\n",bps); //Print bytes per second
        

        temp_bps=bps*2; //We need double speed so we also have to multiply bytes per second by 2
        fprintf(stderr,"temp_bytes/sec: %d\n",temp_bps); //Print bytes per second

                       
        c4=temp_bps/(256*256*256); //Type to calculate the new character to place in the new file created
        temp_bps=temp_bps-c4*256*256*256; //Substract the above character from the new bytes per second
        c3=temp_bps/(256*256); //Type to calculate the new character to place in the new file created
        temp_bps=temp_bps-c3*256*256; //Substract the above character from the new sample rate
        c2=temp_bps/256; //Type to calculate the new character to place in the new file created
        c1=temp_bps-(c2*256); //Type to calculate the new character to place in the new file created

        putchar(c1); //Place the character on the new file
        putchar(c2); //Place the character on the new file
        putchar(c3); //Place the character on the new file
        putchar(c4); //Place the character on the new file

        c1=getchar(); //Block alignment
        c2=getchar(); //

        

        blockal=c2*256+c1;  //Type to calculate Block alignment
        fprintf(stderr,"Block alignment: %d\n",blockal);  //Print block alignment

        putchar(c1);
        putchar(c2);

        if (bps!=samplert*blockal)                       //If bps variable (bytes per second) doesnt equal to the product of sample rate multiplied by block alignment times, print error message and terminate the program
        {
            fprintf(stderr,"Error! bytes/second should be sample rate x block alignment \n");
            return 0;
        }
        
        

        
        c1=getchar(); //Bits per second
        c2=getchar(); //

        
        

        bitps=c2*256+c1;//Type to calculate Bits per second
        fprintf(stderr,"Bits per sample: %d \n",bitps);   //Print bits per second
        
        
 
        if (bitps!=8 && bitps!=16)             //If bitps  variable (bits per second) is different than number 8 or number 16, print error message and terminate the program
        {
            fprintf(stderr,"Error! bits/sample should be 8 or 16 \n");
            return 0;
        }

        if (blockal!=(bitps/8)*mnstr)           //If blockal variable (blockalignment) doesnt equal to the product of bits per second variable divided by 2 and after multiplies by mono/stereo times, print error message and terminate the program
        {  
            fprintf(stderr,"Error! block alignment should be bits per sample / 8 x mono/stereo\n");
            return 0;
        }
        
        putchar(c1); //Place the character on the new file
        putchar(c2); //Place the character on the new file

        c1=getchar(); //Start of data
        c2=getchar(); //
        c3=getchar(); //
        c4=getchar(); //

        
        if (c1!=100 || c2!=97 || c3!=116 ||c4!=97)               //If c1-c4 characters differ from ASCII code letters "d a t a", print error message and terminate the program
        {
            fprintf(stderr,"Error! \"data\" not found");
            return 0;
        }

        putchar(c1); //Place the character on the new file
        putchar(c2); //Place the character on the new file
        putchar(c3); //Place the character on the new file
        putchar(c4); //Place the character on the new file

       
        c1=getchar(); //Size of data chunk
        c2=getchar(); //
        c3=getchar(); //
        c4=getchar(); //

        

        sod=c4*256*256*256+c3*256*256+c2*256+c1;  //Type to calculate size of data
        fprintf(stderr,"Size of data chunk: %d\n",sod); //Print size of data

        putchar(c1); //Place the character on the new file
        putchar(c2); //Place the character on the new file
        putchar(c3); //Place the character on the new file
        putchar(c4); //Place the character on the new file
    
        data_count=8+sfc+12; //Data count is equal to 4 bytes for "WAVE" + 4 bytes for "fmt "+ 4 bytes for the size of format chunk+ 4 bytes for size of format chunck filed + 4 bytes for Size of data
        while ((c1 = getchar()) != EOF) //Get every character left until end of file
        {
            data_count++; //Add every byte left until end of file
            putchar(c1);  //And place every character until end of file to the new file created
        }
        if (data_count < sof)      //If data_count is lower than size of file, print error message and terminate the program
        {
            fprintf(stderr,"Error! insufficient data.\n");
            return 0;
        }
        if (data_count > sof)      //If data_count is higher than size of file, print error message and terminate the program
        {
            fprintf(stderr,"Error! bad file size.\n");
            return 0;
        }   
    }
    
    
}





