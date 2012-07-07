/* final beginners' level with time showing circle! */

void keyboard_lesson(void);
void tutorial_window(void);
int time_control(void);
void user_response(int x1,int y1,int col1,int col2);
void make_sound(int freq,int hold);
void lesson_practice(int lesson_no);
void check_kb_up_down(int button, int state);
void show_number(int n,int x, int y,int col,int font, int size);
void color_text(int x,int y,char *text,int col);
void print_lesson (int x, int y, char c, int color);
void button(int x1,int y1,int x2,int y2,int col, int sty);
void draw_3dbox(int x1,int y1,int x2,int y2,int c1);
void end_lesson(int min,int sec,int eff,int err, int speed);
int continue_close(int min,int sec,int eff,int err,int speed);
void show_summary(int pressed, int correct, int wrong,int correction);
void run_info(int pr, int crct, int w);
void keyboard_but(int x1,int y1,int x2,int y2, int sty);
void undr_line(int x,int y,int no,int len,int gap,int col);
void draw_brief_window(int x1,int y1,int x2,int y2,int state,int c1,int c2);
void up_down_button(int x1,int y1,int x2,int y2,int x3,int y3,int n,int col1,int col2,int col3);
void file_open4_screen(FILE *fp,int initx,int inity,int gap,int col,int tchars,int lchars,int pos);

#define MAX 7


/********************	GLOBAL VARIABLE	********************************/
int LETTER, INCREASE,angle, increase,minute=0, second=0,prev=-1;
time_t start_time, last_time ;
struct time new_time;


float  time_interval=0, min=0, sec=0, eff=0, err=0, speed=0;
float pressed=0, correct= 0, wrong= 0, cpm=0, correction=0;// SCORE BOARD

char lesson[][7] = {"asdf","jkl;","ruty","vbnm","eigh","qwop","cxz,"};
char numeric[][22] ={"0123456789!@#$%^&*()","-_=+\|',<>./?;:{}[]?."};
/* THIS ARRAY STORES THE CHARS SERIALLY THAT WAS  ENTERED RANDOMLY */
char store_chars[500] = {NULL};

char *str0[]={"F1","F2","F3","F4","F5","F6","F7","F8","F9","F10","F11","F12"};
char *str1[]={"`","1","2","3","4","5","6","7","8","9","0","-","=","\\"};
char *str2[]={"Q","W","E","R","T","Y","U","I","O","P","[","]"};
char *str3[]={"A","S","D","F","G","H","J","K","L",";","'","Enter"};
char *str4[]={"Z","X","C","V","B","N","M",",",".","/"};
char *str5[]={"~","!","@","#","$","%","^","&","*","(",")","_","+","|"};

void* key;
unsigned int size_key;

char file_name[][40] ={"c:\\tc\\bin\\1621\\intrdctn.txt",
			"c:\\tc\\bin\\1621\\author.txt",
			"c:\\tc\\bin\\1621\\blevel.txt",
			"c:\\tc\\bin\\1621\\adlevel.txt",
			"c:\\tc\\bin\\1621\\grules.txt",
			"c:\\tc\\bin\\1621\\features.txt",
			"c:\\tc\\bin\\1621\\cinder.txt",
			"c:\\tc\\bin\\1621\\snow.txt",
			"c:\\tc\\bin\\1621\\hansel.txt",
			"c:\\tc\\bin\\1621\\shift.txt"
		     };


/**********************************************************************/

/* this function draws the tutorial window each time it is called */
void tutorial_window(void)
{
	int i,y;
	clearviewport();
	/* back screen */
	draw_3dbox(118,5,getmaxx()-175,getmaxy()-5,6);	/* brown*/
	draw_3dbox(130,20,getmaxx()-190,getmaxy()-20,15);	/*white*/
	setfillstyle(1,4);
	bar(120,7,129,getmaxy()-7);	/* red */

	setlinestyle(SOLID_LINE,1,2);

	for(i=0,y=44;i<16;i++,y+=26)    /* the dots */
	{
		setcolor(7);
		circle(140,y,4);
		setfillstyle(1,7);
		floodfill(140,y,7);
	}
	setcolor(3);  		/* spiral portion of the book */
	for(i=0,y=40;i<16;i++,y+=26)
	{
		ellipse(128,y,140,340,14,11);
		ellipse(128,y+4,140,340,13,9);
	}

	setlinestyle(SOLID_LINE,1,3);
	setcolor(7);
	for(i=0;i<2;i++)
	{
		line(275,50-i,425+i,50-i);    	/* right page right corner */
		line(425-i,50+i,425-i,140);
		line(165-i,353,165-i,430);  	/* right page left corner */
		line(166+i,429-i,325,429-i);
		setlinestyle(SOLID_LINE,1,1);
		setcolor(8);    		/*for shade */
	}

	undr_line(165,81,12,250,18,7);
	draw_3dbox(500,12,620,125,1);
	settextstyle(0,0,1);
	color_text(545,32,"Time",15);
	button(520,45,600,63,15,1);
	button(520,75,600,110,15,1);
	keyboard_lesson();
	setcolor(4);
	circle(550,260,30);
	showMouse();

}

void print_lesson (int x, int y, char c, int color)
{
	settextstyle(0,0,1);
	setcolor(color);
	char cs[2];
	cs[0] = c;
	cs[1]= '\0';
	outtextxy(x,y,cs);
}

void keyboard_but(int x1,int y1,int x2,int y2, int sty)
{
	int col1,col2;
	col1 = 15;
	col2 =8;
	if(sty)
		col1 ^=col2 ^=col1 ^=col2;

	setlinestyle(SOLID_LINE,1,2);

	setcolor(col1);
	line(x1,y1,x1,y2);
	line(x1,y1,x2,y1);
	line(x1-1,y1-1,x1-1,y2+1);
	line(x1-1,y1-1,x2+1,y1-1);

	setcolor(col2);
	line(x1,y2,x2,y2);
	line(x2,y2,x2,y1);
	line(x2+1,y1-1,x2+1,y2+1);
	line(x2+1,y2+1,x1-1,y2+1);
}

/* keyboard of lesson screen */
void keyboard_lesson(void)
{

	int z,i,j;
	setfillstyle(1,7);
	bar(60,303,532,435);
	keyboard_but(60,305,532,435,0);

	settextstyle(0,0,1);
	keyboard_but(75,315,106,330,0);//ESC button
	color_text(78,318,"Esc",8);

	for(z=126;z<490;z+=33)
		keyboard_but(z,315,z+28,330,0); //DRAWING BUTTONS 4 1ST ROW (FUNCTION KEYS)

	for(i=130,j=0;i<500;i+=33,j++)
		color_text(i,318,str0[j],8); //to write char in first row

	for(z=75;z<460;z+=29)
		keyboard_but(z,340,z+25,355,0);    //Keep the keyboard button  of 2nd row up

	for(i=85,j=0;i<490;i+=29,j++){
		if(j>10)
			color_text(i-5,346,str1[j],8);
		else
			color_text(i,343,str1[j],8);  //to write char in 2nd row
	}
	outtextxy(404,337,"_");
	outtextxy(436,343,"+");
	outtextxy(466,343,"|");

	keyboard_but(481,340,516,355,0);   // BACKSPACE
	color_text(491,343,"<-",8);

	keyboard_but(75,358,106,373,0);  //  tab
	color_text(80,359,"<-",8);
	color_text(83,365,"->",8);

	outtextxy(85,349,"~");
	outtextxy(360,397,"<");
	outtextxy(390,397,">");
	outtextxy(418,397,"?");

	for(z=110;z<460;z+=30)
		keyboard_but(z,358,z+26,373,0);   //Keep the keyboard button  of 3rd row up

	for(i=120,j=0;i<460;i+=30,j++){
		if(j>9)
			color_text(i+5,363,str2[j],8);
		else
			color_text(i,361,str2[j],8);  //to write char in 3rd row
	}
	outtextxy(416,361,"{");
	outtextxy(446,361,"}");

	for(z=119;z<440;z+=30)
		keyboard_but(z,376,z+26,391,0);   //Keep the keyboard button  of 4th row up

	for(i=129,j=0;i<460;i+=30,j++)
	{
		settextstyle(0,0,1);         //to write char in 4th row
		if(j==9)
			color_text(i+5,381,str3[j],8);
		else if(j==10)
			color_text(i+6,385,str3[j],8);
		else
			color_text(i,379,str3[j],8);
	}
	outtextxy(393,379,":");
	outtextxy(426,379,"\"");

	for(z=143;z<420;z+=30)
		keyboard_but(z,394,z+26,409,0);    //Keep the keyboard button  of 5th row up

	for(i=153,j=0;i<450;i+=30,j++)
	{
		settextstyle(0,0,1);

		if(j>6)
			color_text(i+4,399,str4[j],8);

		else
			color_text(i,397,str4[j],8); //to write char in 5th row


	}

	keyboard_but(165,412,396,427,0); //space
	keyboard_but(448,376,516,391,0);
	keyboard_but(470,358,516,373,0);  //enter
	setcolor(7);
	line(470,373,515,373);
	line(470,374,515,374);
	line(470,375,515,375);
	line(471,376,515,376);

	keyboard_but(75,376,115,391,0); // CAPS LOCK BUTTON
	settextstyle(2,0,4);
	color_text(79,377,"C.Lock",8);

	keyboard_but(75,394,139,409,0);          //l-shift
	outtextxy(82,393,"^");
	outtextxy(450,393,"^");   //pin-point of shift button
	line(451,400,451,405);   // 434these 4 lines make the long sticky portion of shift-button
	line(453,400,453,405);
	line(451,405,453,405);
	line(83,400,83,405);
	line(85,400,85,405);
	line(83,405,85,405);
	settextstyle(2,0,4);
	setcolor(8);
	outtextxy(85,395," Shift"); // left shift


	keyboard_but(443,394,516,409,0);         //r-shift
	outtextxy(458,395," Shift");

	/*ctrl,window,alt*/
	for(i=75;i<136;i+=30)
		 keyboard_but(i,412,i+26,427,0);

	settextstyle(2,0,4);
	outtextxy(78,413,"Ctrl");
	outtextxy(141,413,"Alt");

	/*LEFT- window button*/
	rectangle(117,415,127,424);
	line(122,415,122,424);
	line(117,419,127,419);
	for(i=415;i<424;i+=2)
		for(z=115;z>107;z-=2)
			putpixel(z,i,8);


	/*ctrl,alt,window,task*/
	for(i=400;i<500;i+=30)
		 keyboard_but(i,412,i+26,427,0);

	/* RIGHT- window button*/
	rectangle(442,415,452,424);
	line(447,415,447,424);
	line(442,419,452,419);
	for(i=415;i<424;i+=2)
		for(z=440;z>433;z-=2)
			putpixel(z,i,8);

	settextstyle(2,0,4);
	outtextxy(405,413,"Alt");
	outtextxy(492,413,"Ctrl");
	rectangle(467,415,477,424);
	for(i=417;i<422;i+=2)
		  line(470,i,474,i);
}

/* shows the summary of typing */
void show_summary(int min, int sec,int acc, int err, int speed)
{
	/* min= required minute, sec= required seconds, acc= percentage of accuracy,
	   err= percentage of pressing b.space, speed= typing speed */

		char ch[5];
		int j1,m,n,i,x=180,y;
		char result[][50]= {"Time Elapsed:-    min    sec","Accuracy  :    %","Backspace :    %","Speed[cpm]:"};

	    //	draw_brief_window(200,90,380,250,1,6,0); // agerta
		draw_brief_window(170,90,410,250,1,6,0);

		settextstyle(0,0,1);
		color_text(182,94,"Result",15);
		settextstyle(2,0,5);//2,0,5    3
		setcolor(6);

		for(i=0,y=120;i<4;i++,y+=18){
			outtextxy(x,y,result[i]);
			outtextxy(x+1,y,result[i]);
		}

	      //	outtextxy(215,210,"Adjacent speed:");  */

		show_number(min,300,120,4,2,5); // min
		show_number(min,301,120,4,2,5);
		show_number(sec,355,120,4,2,5); //sec
		show_number(sec,356,120,4,2,5);
		show_number(acc,268,138,4,2,5); // accuracy
		show_number(acc,269,138,4,2,5); // accuracy
		show_number(err,268,156,4,2,5); // error
		show_number(err,269,156,4,2,5); // error
		show_number(speed,268,174,4,2,5); // speed
		show_number(speed,269,174,4,2,5); // speed

		if(!minute && !second){
			setfillstyle(1,0);
			bar(175,120,405,135);
			color_text(250,115,"TIME IS UP",6);
			color_text(251,115,"TIME IS UP",6);
		}

		setcolor(4);

		if(min ||sec)
		{
			if(acc || err || speed){
				if(acc<=35)
					outtextxy(315,138,"Beginner");

				else if(acc>35 && acc<= 60)
					outtextxy(315,138,"Intermediate");

				else if(acc>60 && acc<= 95 )
					outtextxy(315,138,"Advanced");

				else
					outtextxy(315,138,"Expert");

				if(err <=5)
					outtextxy(315,156,"Expert");

				else if(err>5 && err<=10)
					outtextxy(315,156,"Advanced");

				else if(err>10 && err<=20)
					outtextxy(315,156,"Intermediate");

				else
					outtextxy(315,156,"Beginner");

				if(speed<=100)
					outtextxy(315,174,"Beginner");

				else if( speed>100 && speed<=160)
					outtextxy(315,174,"Intermediate");

				else if( speed>160 && speed<=220)
					outtextxy(315,174,"Advanced");

				else
					outtextxy(315,174,"Expert");

			}

		}
}

void end_lesson(int min,int sec,int eff,int err, int speed)
{
	int change=0,y,x;
	show_summary(min, sec, eff, err, speed);
	draw_3dbox(260,220,320,240,15);
	settextstyle(0,0,1);
	color_text(280,227,"Ok",3);
	showMouse();
	while(1)
	{
		while(1)
		{
			x=getMouseX(); /* get the mouse position*/
			y=getMouseY();
			if(x>=260&&x<=320&&y>=220&&y<=240 && !change)
			{
				change = 1;
				settextstyle(0,0,1);
				hideMouse();
				draw_3dbox(260,220,320,240,6);	/* change the color of the box*/
				/* change the text color*/
				color_text(280,227,"Ok",15);   /*cursor on yes*/
				showMouse();
			}

			if((x<=260||x>=320||y<=220||y>=240)&& change)
			{
				change = 0;
				hideMouse();
				draw_3dbox(260,220,320,240,15);
				/* when mouse moves away change the color to normal one*/
				color_text(280,227,"Ok",3);
				showMouse();         /*cursor on yes/no*/
			}

			if(mouseClicked())
			{
				x=getMouseX();       /*get the position where mouse is clicked*/
				y=getMouseY();
				while(1)
					if(mouseReleased())		/* get the position*/
						break;			/* where mouse is clicked*/
				break;					/* and released */
			}
		}/*end of while 2 which changes color of button*/

		/*check the position of mouse clicked*/
		if(x>=260&&x<=320&&y>=220&&y<=240)  // back
		{
			hideMouse();
			up_down_button(260,220,320,240,280,227,19,15,15,6);
			break;
		}
	}/*end of while 1*/

}

int continue_close(int min, int sec, int eff, int err, int speed)
{
	unsigned int sum;
	void* summary;
	int x,y,j=-2,pr=-1,i;

    //	sum=imagesize(200,90,380,250);
	sum=imagesize(170,90,410,250);
	summary= malloc(sum);
	getimage(170,90,410,250,summary);

	show_summary(min,sec,eff,err,speed);
	draw_3dbox(210,220,280,240,15);
	draw_3dbox(305,220,370,240,15);
	settextstyle(0,0,1);
	color_text(214,227,"Continue",3);
	color_text(317,227,"Close",3);
	showMouse();
	while(1)
	{
		while(1)
		{
			x=getMouseX(); /* get the mouse position*/
			y=getMouseY();
			for(i=0;i<2;i++)
			{
				if(x>=210+(i*95)&&x<=280+(i*90)&&y>=220&&y<=240 )
				{
					j=i;     /* check the position*/
					break;
				}
			}
			settextstyle(0,0,1);
			if(j>=0&&j<2&& j!=pr)
			{
				hideMouse();
				draw_3dbox(210+(j*95),220,280+(j*90),240,6);	/* change the color of the box*/
				/* change the text color*/
				if(j)
					color_text(317,227,"Close",15);	/*cursor on no*/
				else if(!j)
					color_text(214,227,"Continue",15);   /*cursor on yes*/
				showMouse();
			}
			if(j!=pr && pr>=0 && pr<2)
			{
				hideMouse();
				draw_3dbox(210+(pr*95),220,280+(pr*90),240,15);
				/* when mouse moves away change the color to normal one*/
				if(pr)
					color_text(317,227,"Close",3);
				else if(!pr)
					color_text(214,227,"Continue",3);
				showMouse();         /*cursor on yes/no*/
			}
			pr = j;	/* keeps the current postion to use next time as previous*/
			j = -1;
			if(mouseClicked())
			{
				x=getMouseX();       /*get the position where mouse is clicked*/
				y=getMouseY();
				break;
			}
		}/*end of while 2 which changes color of button*/

		/*check the position of mouse clicked*/
		if(x>=210&&x<=280&&y>=220&&y<=240)  // continue
		{
			hideMouse();
			up_down_button(210,220,280,240,214,227,18,15,15,6);
			putimage(170,90,summary,COPY_PUT);
			//showMouse();     /*if clicked on back return to previous stage*/
			free(summary);
			return 0;
		}
		else if(x>=305&&x<=370&&y>=220&&y<=240)
		{
			hideMouse();
			up_down_button(305,220,370,240,317,227,23,15,15,6);
			free(summary);   //if clicked on close exit from the lesson
			time_interval=0, min=0, sec=0, minute=0,second=0,eff=0, err=0, speed=0;
			pressed=0, correct= 0, wrong= 0, cpm=0, correction=0;
			showMouse();
			return 1;
		}
	}/*end of while 1*/
}

/* IF USER JUST RUNS THE PROGRAM, WAIT  UNTIL 'ENTER'
   IS PRESSED TO FIND THE STARTING TIME */
void user_response(int x1,int y1,int col1,int col2)
{
	void* ext;
	unsigned int size; int line, choice;
	size = imagesize(x1,y1,x1+110,y1+50);	// calculate the size of the bar
	ext = malloc(size);			// allocate memory to hold the current image to use later
	getimage(x1,y1,x1+110,y1+50,ext);		// grab the image

	// WAIT  FOR USER RESPONSE
	for(line=0;;line++)
	{
		draw_3dbox(x1,y1,x1+110,y1+50,col1);
		settextstyle(2,0,5);
		color_text(260,135,"Press ENTER",col2);
		color_text(275,155,"to START",col2);

		delay(500);
		putimage(x1,y1,ext,COPY_PUT);         // blink
		delay(300);
		fflush(stdin);
		flushall();
		if(kbhit())
			choice=getch();
		if(choice==13)  //when Enter is pressed,lesson starts
			break;
	}

	free(ext);

}

void show_number(int n,int x, int y,int col,int font, int size)
{
	char inch[20];
	sprintf(inch,"%d",n);
	settextstyle(font,0,size);
	color_text(x,y,inch,col);

}

void run_info_window(){
	draw_3dbox(500,125,620,215,1);
	setlinestyle(SOLID_LINE,1,3);
	setcolor(1);
	line(502,125,618,125);
	setcolor(7);
	line(501,125,501,125);
	button(510,120,610,205,15,1);
	settextstyle(0,0,1);
	color_text(518,130,"Pressed:",4);
	color_text(518,150,"Correct:",4);
	color_text(518,170,"Wrong  :",4);
	color_text(518,190,"B.space:",4);
}

void run_info(int pr, int crct, int w, int crtn){
	/* pr= pressed, crct= correct, w= wrong , crtn= correction */

	setfillstyle(1,15);
	bar(582,130,609,200);

	show_number(pr,584,130,4,0,1);
	show_number(crct,584,150,4,0,1);
	show_number(w,584,170,4,0,1);
	show_number(crtn,584,190,4,0,1);

}
void summary_content()
{
	time(&last_time);
	time_interval = last_time - start_time;
	if(time_interval <1)
		time_interval = 1;

	eff= (correct/ pressed)*100;
	err= (correction / pressed)*100;
	speed= (correct/time_interval)*60; // pressed er basis e ber korbo?

}

void check_kb_up_down(int button, int state){

	int z,ch1;
	if(button==8)
		keyboard_but(481,340,516,355,state);   // BACKSPACE

	else if(button==32)
		keyboard_but(165,412,396,427,state);  //space button

	else if(button==27)
		keyboard_but(75,315,106,330,state);  // esc
	else{
		for(z=0;z<14;z++){
			if(button==*str1[z]){
				keyboard_but(75+29*z,340,100+29*z,355,state);
				break;
			}

			if(button==*str5[z]){
				if(z>7)
					keyboard_but(75,394,139,409,state);          //l-shift
				else
					keyboard_but(443,394,516,409,state);          //r-shift

				keyboard_but(75+29*z,340,100+29*z,355,state);
				break;
			}
		}

		for(z=0;z<10;z++){
			if(button==*str2[z]||button==*str2[z]+32){  //drawn again the keyboard button when a definite
				if(button==*str2[z]){
					if(z>6)
						keyboard_but(75,394,139,409,state);
					else
						keyboard_but(443,394,516,409,state);
				}
				keyboard_but(110+30*z,358,136+30*z,373,state);
				break;
			}
		}

		for(z=10; z<12; z++){
			if(button==*str2[z])
				keyboard_but(110+30*z,358,136+30*z,373,state);
		}
		if(button==123 || button==125){
			keyboard_but(75,394,139,409,state);
			if(button==123)
				keyboard_but(410,358,436,373,state);
			else
				keyboard_but(440,358,466,373,state);
		}

		for(z=0;z<9;z++){
			if(button==*str3[z]||button==*str3[z]+32){
				if(button==*str3[z]){
					if(z<6)
						keyboard_but(443,394,516,409,state);
					else
						keyboard_but(75,394,139,409,state);
				}

				keyboard_but(119+30*z,376,145+30*z,391,state);
				break;
			}
		 }
		 for(z=9; z<11; z++){
			if(button==*str3[z])
			       keyboard_but(119+30*z,376,145+30*z,391,state);
		 }
		 if(button==58 || button==34){
			keyboard_but(75,394,139,409,state); // l-shift
			if(button==58)
				keyboard_but(389,376,415,391,state);
			else
				keyboard_but(419,376,445,391,state);
		 }


		 for(z=0;z<7;z++){      // definite key of 5th row
			if(button==*str4[z]||button==*str4[z]+32){
				if(button==*str4[z]){
					if(z<4)
						keyboard_but(443,394,516,409,state);
					else
						keyboard_but(75,394,139,409,state);
				}
				keyboard_but(143+30*z,394,169+30*z,409,state);
				break;
			}
		 }
		 for(z=7;z<10;z++){      // , . / last 3 keys of 5th row
			if(button==*str4[z]){
				keyboard_but(143+30*z,394,169+30*z,409,state);
				break;
			}
		 }
		 if(button==60 || button==62 || button==63){ // < > ?
			keyboard_but(75,394,139,409,state); // l-shift
			if(button==60)
				keyboard_but(353,394,379,409,state);
			else if(button==62)
				keyboard_but(383,394,409,409,state);
			else
				keyboard_but(413,394,439,409,state);
		 }
	}
}

int time_control(){
	if (prev != new_time.ti_sec)//show hour minute and second when prev!=ti.te_sec
	{                               //that is after 1 second
		setfillstyle(1,4);
		setcolor(4);
		pieslice(550,260,angle,angle+1,30);
		angle-= INCREASE;
		if(increase==90)
			angle=359;
		if(increase==180)
			angle=269;
		if(increase==270)
			angle=179;
		sec++;
		increase+= INCREASE;
		if(sec==60){
			min++;	sec=0;
		}
		setfillstyle(1,15);
		bar(569,47,589,60);
		if(second<=9){
			if(!second){
				bar(550,47,560,60);
				if(!minute){
					color_text(574,50,"00",4);
					outtextxy(550,50,"0");
					setfillstyle(1,4);
					setcolor(4);
					pieslice(550,260,90,120,30);
					summary_content();
					end_lesson(min,sec,eff,err,speed);
					return 1;

				}
				minute--;
				second=59;
				show_number(second,574,50,4,0,1);
			}
			else{
				outtextxy(574,50,"0");
				show_number(second,582,50,4,0,1);
			}
		}

		else
			show_number(second,574,50,4,0,1);
		show_number(minute,552,50,4,0,1);
		second--;
		prev = new_time.ti_sec;

	}

	return 0;

}

void lesson_practice(int lesson_no,int num,int MINUTE,int angleINCREASE)
{
/* INCREASE= will control time, MINUTE= given time limit of typing */

	int j1,ch1,x1,y1,time_up;
	int char_x, char_y,i,choice,dummy_choice,line,z;
	int rndm,store; /* 'store' is used to store chars serially in
				store array */
	prev= -1;
	time_interval=0, min=0, sec=0, eff=0, err=0, speed=0;
	pressed=0, correct= 0, wrong= 0, cpm=0, correction=0;
	minute=MINUTE, INCREASE= angleINCREASE, second=0;

	char_x = 173;
	char_y = 72;

	tutorial_window();
	run_info_window();
	hideMouse();

	if(!num)
		LETTER= 4;

	else if(!lesson_no)
		LETTER=20;

	line = 1;
	for(i=1,store=0; line<MAX ;i++,store++)
	{
		rndm = random(LETTER); // randomly seeks chars
		if(!num){
			store_chars[store]= lesson[lesson_no-1][rndm];
			print_lesson(char_x, char_y, lesson[lesson_no-1][rndm],1);
		}

		else if(!lesson_no){
			store_chars[store]= numeric[num-1][rndm];
			print_lesson(char_x, char_y, numeric[num-1][rndm],1);
		}
		char_x +=8; //for next character

		if(i%4==0)       // GIVING SPACE AFTER EVERY 4 CHARS
		{
			char_x +=8;
			store++;
			store_chars[store]=' ';
		}

		if(char_x >405)    // NEXT LINE
		{
			char_x = 173;
			char_y+= 36;
			line++;
		}
	}
	setcolor(4);
	outtextxy(542,50,"0");
	outtextxy(562,50,":");
	outtextxy(574,50,"00");
	show_number(minute,550,50,4,0,1);
	run_info(pressed,correct,wrong,correction);
	user_response(250,130,1,3);
	time(&start_time);

	settextstyle(2,0,5);
	color_text(535,76,"ESC to",3);
	color_text(536,76,"ESC to",3);
	color_text(524,92,"quit/pause",3);
	color_text(525,92,"quit/pause",3);
	char_x= 173; 	char_y= 90;  line =1;  i=0;

	dummy_choice= 'A'; //just to initialize the drawing of a key
	increase=0, angle=89;
	while(1)
	{
	      gettime (&new_time);
	      time_up= time_control();
	      if(time_up)
			return;


	      if(line<7){
			color_text(char_x,char_y+1,"_",4);
			color_text(char_x,char_y-23,"^",4);
	      }

	      if(kbhit())
	      {
			check_kb_up_down(dummy_choice,0);

			choice= getch();  // ASSIGN USER INPUT TO 'CHOICE'
			dummy_choice= choice;
			pressed++;

			check_kb_up_down(choice,1);

			if(line>6)
			{
				summary_content();
				end_lesson(min,sec,eff,err,speed);
				return;
			}
			if(choice==27 )  // ESC
			{
				pressed--;
				make_sound(2000,100);
				if(i>0)
					summary_content();

				z = continue_close(min,sec,eff,err,speed);
				if(z)
					return;
				else
					continue;
			}
			else if(choice==0) // error checking for function keys
			{
				ch1=getch();
				if(ch1==80||ch1==72||ch1==75||ch1==77)   //error checking  to avoide right,left,up
					continue;
			}

			else if(choice==9)
				continue;    //error checking for tab

			else if(choice==8)  	// BACKSPACE
			{
				if(i>0)
				{
					correction++;
					if(char_x<=173){
						setfillstyle(1,15);
						bar(char_x+233,char_y-36,char_x+243,char_y-29);
						color_text(char_x,char_y+1,"_",15);
						color_text(char_x,char_y-23,"^",15);
						char_y-=36;
						char_x+=240;

						color_text(char_x-8,char_y+1,"_",4);
						color_text(char_x-8,char_y-23,"^",4);

					}

					else{
						setfillstyle(1,15);
						bar(char_x-8, char_y, char_x,char_y+7);
						color_text(char_x,char_y+1,"_",15);
						color_text(char_x-8,char_y+1,"_",4);
						color_text(char_x,char_y-23,"^",15);
						color_text(char_x-8,char_y-23,"^",4);
					}
					--i;
					char_x-=8;
					sound(1000);
					delay(100);
					nosound();
				}
			}

			else{

				if(choice==store_chars[i]){  			//letter is ok!
					print_lesson(char_x,char_y,choice,4);
					correct++;
				}

				else if(store_chars[i] !=choice && choice==' ')
				{
					char choice1 = '-';	//when space is pressed instead of any key, print dash
					print_lesson(char_x,char_y,choice1,9);
					make_sound(500,100);
					wrong++;
				}
				else
				{
					print_lesson(char_x, char_y,choice,9);
					make_sound(500,100);
					wrong++;
				}

				color_text(char_x+8,char_y-23,"^",4);
				color_text(char_x,char_y-23,"^",15);
				color_text(char_x+8,char_y+1,"_",4);
				color_text(char_x,char_y+1,"_",15);
				char_x +=8;
				if(char_x > 405)
				{
					color_text(char_x,char_y+1,"_",15);
					color_text(char_x,char_y-23,"^",15);
					char_x = 173;
					char_y +=36;
					line++;
				}
				i++;

			}  // end of else or default typing

			run_info(pressed,correct,wrong,correction);
	      } // end of the initial 'if'
	}  // end of while
}

void advanced_level(int file_no,int MINUTE, int angleINCREASE){

	FILE *file;
	file= fopen(file_name[file_no],"r");

	char choice[2],comp;
	// line & i will keep track wid total lines and chars respectively
	int i=0,chars=0, file_pointer,line,z,char_x,char_y,dummy_choice;
	int j1,ch1,x1,y1,time_up;

	prev= -1;
	time_interval=0, min=0, sec=0, eff=0, err=0, speed=0;
	pressed=0, correct= 0, wrong= 0, cpm=0, correction=0;
	minute=MINUTE, INCREASE= angleINCREASE,second=0;
	tutorial_window();
	hideMouse();

	file_pointer=0; choice[1]='\0';

	setcolor(4);
	settextstyle(0,0,1);
	outtextxy(542,50,"0");
	outtextxy(562,50,":");
	outtextxy(574,50,"00");
	show_number(minute,550,50,4,0,1);
	user_response(250,130,1,3);
	time(&start_time);

	settextstyle(2,0,5);
	color_text(535,76,"ESC to",3);
	color_text(536,76,"ESC to",3);
	color_text(524,92,"quit/pause",3);
	color_text(525,92,"quit/pause",3);

	dummy_choice= 'A'; //just to initialize the drawing of a key
	increase=0, angle=89;

	file_open4_screen(file,173,72,36,1,6,30,0);

	while(!feof(file)){

		i=0;char_x=173;char_y=90; line=0; chars=0;
		rewind(file);
		fseek(file,file_pointer,0);

		while(line<6){
			if(feof(file)){
				summary_content();
				end_lesson(min,sec,eff,err,speed);
				return;
				//break;
			}
			gettime (&new_time);
			time_up= time_control();
			if(time_up)
				return ;

			if(i>=0){
				color_text(char_x+8*i,(char_y+36*line)+1,"_",4);
				color_text(char_x+8*i,(char_y+36*line)-23,"^",4);
			}

			if(kbhit()){

				check_kb_up_down(dummy_choice,0);
				choice[0]= getch(); // user input
				dummy_choice= choice[0];
				pressed++;
				check_kb_up_down(choice[0],1);

				if(chars>29){
					color_text((char_x+i*8),(char_y+36*line)+1,"_",15);
					color_text((char_x+i*8),(char_y+36*line)-23,"^",15);
					i=0; line++; chars=0;
				}

				if(choice[0]==27 )  // ESC
				{
					pressed--;
					make_sound(2000,100);
					if(i>0)
						summary_content();

					z = continue_close(min,sec,eff,err,speed);
					if(z)
						return;
					else
						continue;
				}

				if(choice[0]==0){ // error checking for function keys
					int ch1=getch();
					if(ch1==80||ch1==72||ch1==75||ch1==77)   //error checking  to avoide right,left,up
						continue;
				}

				else if(choice[0]==9)
					continue;    //error checking for tab

				else if(choice[0]==8){  //BACKSPACE
					correction++;

					if(i>0 || line>0){
						if(i>0){
							file_pointer--;
							fseek(file,-1,SEEK_CUR);
							setfillstyle(1,15);
							bar(char_x+i*8,char_y+36*line,char_x+(i*8)-8,char_y+7+36*line);
							color_text((char_x+i*8)-8,(char_y+36*line)+1,"_",4);
							color_text(char_x+i*8,(char_y+36*line)+1,"_",15);
							color_text((char_x+i*8)-8,(char_y+36*line)-23,"^",4);
							color_text(char_x+i*8,(char_y+36*line)-23,"^",15);
							i--; chars--;
						}

						if(i>29){
							line++; i=0;chars=0;
						}

					}
					make_sound(1000,100);

				}

				else{
					file_pointer++; correct++;
					fscanf(file,"%c",&comp);
					setcolor(4);
					if(comp=='\n'){
						i=0; chars=1; line++; continue;

					}
					if(comp!=choice[0] && choice[0]==' ')
					{
						char choice1 = '-';	//when space is pressed instead of any key, print dash
						print_lesson(char_x+i*8,char_y+36*line,choice1,9);
						make_sound(500,100);
						wrong++; correct--;
					}

					else if(comp != choice[0]){
						wrong++; correct--;
						setcolor(9);
						make_sound(500,100);
						outtextxy(char_x+i*8,char_y+36*line,choice);
					}
					else
						outtextxy(char_x+i*8,char_y+36*line,choice);

					color_text((char_x+i*8)+8,(char_y+36*line)-23,"^",4);
					color_text(char_x+i*8,(char_y+36*line)-23,"^",15);
					color_text((char_x+i*8)+8,(char_y+36*line)+1,"_",4);
					color_text(char_x+i*8,(char_y+36*line)+1,"_",15);
					i++; chars++;
				}
			}

		}
		if(feof(file))
			break;
		setfillstyle(1,15);
		bar(165,56,417,300);
		undr_line(165,81,12,250,18,7);
		file_open4_screen(file,173,72,36,1,6,30,file_pointer);
	}
	fclose(file);
	closegraph();
}









