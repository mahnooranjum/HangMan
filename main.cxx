#include "graphics.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

//offset
int xOff=100,yOff=100;

int StateCheck =0;
void InitilizeGallows()
{

	//Gallow
	setcolor(COLOR(165,42,42));
	for (int i =0 ; i<12 ; i++)
	{
	line(xOff+100-10,yOff+-20+i,xOff+400-10,yOff+-20+i);//topwood
	}

		for (int i =0 ; i<12 ; i++)
	{
	line(xOff+ 400-10+i,yOff+-20+i,xOff+ 400-10+i,600);//rightwood
	}
	
	setcolor(COLOR(165+50,42+50,42+50));
	for (int i =0 ; i<6 ; i++)
	{
	line(xOff+100+i-3,yOff+10,xOff+100+i-3,yOff+-20);//rope
	}

	//Gallow
}

void State1()
{
	///face
	setcolor(COLOR(255,255,255));
	setfillstyle(1,COLOR(255,255,0));
	fillellipse(xOff+100,yOff+50,40,40);//face outline
	
	setfillstyle(1,COLOR(0,0,0));
	fillellipse(xOff+80,yOff+35,10,10);//eye
	fillellipse(xOff+120,yOff+35,10,10);//eye
	circle(xOff+100, yOff+50, 40);
	fillellipse(xOff+100,yOff+65,15,15);//mouth
	//face;
}

void State2()
{
	//torso
	setfillstyle(1,COLOR(255,255,0));
	fillellipse(xOff+100,yOff+190,30,100);
	//torso

}

void State3()
{
	//rightArm
	setcolor(COLOR(255,255,0));
	for (int i =0 ; i<8 ; i++)
	{
	line(xOff+100,yOff+120+i,xOff+200,yOff+150+i);
	}
	//rightArm

}

void State4()
{
	//leftArm
	setcolor(COLOR(255,255,0));
	for (int i =0 ; i<8 ; i++)
	{
	line(xOff+100,yOff+120+i,xOff+0,yOff+150+i);
	}
	//leftArm
}

void State5()
{
	//rightLeg
	setcolor(COLOR(255,255,0));
	for (int i =0 ; i<20 ; i++)
	{
	line(xOff+100,yOff+250+i,xOff+200,yOff+400+i);
	}
	//rightleg
}

void State6()
{

	//leftLeg
	setcolor(COLOR(255,255,0));
	for (int i =0 ; i<20 ; i++)
	{
	line(xOff+100,yOff+250+i,xOff+0,yOff+400+i);
	}
	//leftleg

}

void StateChange(int chk) /// state Change func
{
	switch(chk)
	{
	case 1:
		State1(); //face
		break;
	
	case 2:
		State1();//face and torso
		State2();
		break;

	case 3:
		State1();// face torso right arm
		State2();
		State3();
		break;
	
	case 4:
		State1(); // face torso right and left arm
		State2();
		State3();
		State4();
		break;
	
	case 5:
		State1(); // face torso right and left arm plus right leg
		State2();
		State3();
		State4();
		State5();
		break;

	case 6:
		State1(); // full body
		State2();
		State3();
		State4();
		State5();
		State6();
		break;
	
	
	}
}


char input;
char words[10][50] ={{"cat\0"},{"dog\0"},{"alligator\0"},{"horse\0"},{"donkey\0"},{"zebra\0"},{"monkey\0"},{"crow\0"},{"dolphin\0"},{"turtle\0"}};///word list //can add more
char alpha [50] ={ 'A',' ','B',' ','C',' ','D',' ','E',' ','F',' ','G',' ','H',' ','I',' ','J',' ','K',' ','L',' ','M',' ','O',' ','P',' ','Q',' ','R',' ','S',' ','T',' ','U',' ','V',' ','W',' ','X',' ','Y',' ','Z'};
char inp[25];//input string
int inpIdx;//input index
char MYWORD[50];

bool InputValid(char input)
{		int i=0;
	while(inp[i]!=NULL && i <25)/// checking for duplications
	{
	if (input==inp[i])
		return false;
	i++;
	}
	return true;
}
void Letters()
{
	for(int i=0;i<50;i=i+2)
	{
		setcolor(COLOR(255,255,255));
		
		for(int j =0; j<inpIdx+1; j++) // cheking old enteries with uper and lower cases
		{
			if (inp[j]== tolower(alpha[i]) || inp[j] == alpha[i])
				setcolor(COLOR(255,0,0));
		}
		char now[3] = {alpha[i],' ',0 } ; // just to add spaces and null
			
		outtext(now);
	
	}

}

bool GamePrompt()// places the dashes equal to the no of letters plus the calid letters
{int complete=0;
	outtext("                 \n");
	for (int i=0;i<strlen(MYWORD);i++)
	{ bool flag = false;
	
		for (int j =0 ;j<inpIdx+1;j++)
		{
			if(inp[j]==MYWORD[i]) /// checking letter
			{flag=true; complete++; break;}
		}

		if (flag) // letter found
		{char now[3] = {toupper(MYWORD[i]),0 }; outtext(now); }
		else // places dash 
		{outtext("_ ");}
				
	}
if (complete==strlen(MYWORD)) /// checking if word is complete
			return true;
		else
		return false;
}

bool RefreshViewport() // clear and redraw
{	
	clearviewport();
	InitilizeGallows();
	Letters();	
	StateChange(StateCheck);
	return GamePrompt();
}

bool GameWord(char inp) // checking input is the part of the word or not
{
	for(int i=0 ;i<strlen(MYWORD);i++)
	{
	 if (inp==MYWORD[i])
		 return true;
	
	}
	return false;
}


int main( )
{	time_t t;
	srand(time(NULL));
	int randNo = rand()%10;//rand betwwen 0 and 10
	
	memcpy(MYWORD,words[randNo],50);// copying
	
	int size= strlen(MYWORD);

	printf("%s","enter here\n");

	inpIdx=0;
    initwindow(600, 600, "Hang Man");
	InitilizeGallows();
	setcolor(COLOR(255,255,255));
	Letters();
	GamePrompt();
	//outtext(alpha);
	
	

	while (1)
    {
		


	scanf("%c",&input);
	//outtext("test");
	////
	////////INSERT HANG MAN LOGIC HERE
	////
	bool inputValidity =InputValid(input);
	if (inputValidity)
	{
		inp[inpIdx]=input;
		inpIdx++;
	}

	if (input =='0') /// exit check
		break;
	if ((!GameWord(input)) && (inputValidity))/// input check
	{StateCheck++;  }

	if (StateCheck>=6)//gameover
	{	
		clearviewport();
		InitilizeGallows();
		StateChange(6);
		outtext("GAME OVER");
		break;
	}
		
	if (RefreshViewport())// if true game completes
	{
		clearviewport();
		InitilizeGallows();
		StateChange(StateCheck);
		GamePrompt();
		outtext("   GAME COMPLETE");
		break;
	
	}
	scanf("%c",&input);
    delay(500);
    }

	getch();
	getch();
    return 0;
}