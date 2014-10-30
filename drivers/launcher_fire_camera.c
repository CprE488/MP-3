
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>

#define FRAME_BUFFER_ADDRESS 0x10000000
#define WAIT 0
#define BLACK1 1
#define WHITE1 2
#define WHITE1_CONF 3
#define BLACK2 4
#define BLACK2_CONF 5
#define WHITE2 6
#define WHITE2_CONF 7
#define BLACK3 8
#define BLACK3_CONF 9
#define WHITE3 10
#define WHITE3_CONF 11
#define TARGET 12
#define TARGET_CONF 13
#define WHITE4 14
#define WHITE4_CONF 15
#define BLACK4 16
#define BLACK4_CONF 17
#define WHITE5 18
#define WHITE5_CONF 19
#define BLACK5 20
#define BLACK5_CONF 21
#define WHITE6 22
#define WHITE6_CONF 23
#define BLACK6 24
#define BLACK6_CONF 25


#define BLACK 2
#define WHITE 1

#define LAUNCHER_NODE           "/dev/launcher0"
#define LAUNCHER_FIRE           0x10
#define LAUNCHER_STOP           0x20
#define LAUNCHER_UP             0x02
#define LAUNCHER_DOWN           0x01
#define LAUNCHER_LEFT           0x04
#define LAUNCHER_RIGHT          0x08
#define LAUNCHER_UP_LEFT        (LAUNCHER_UP | LAUNCHER_LEFT)
#define LAUNCHER_DOWN_LEFT      (LAUNCHER_DOWN | LAUNCHER_LEFT)
#define LAUNCHER_UP_RIGHT       (LAUNCHER_UP | LAUNCHER_RIGHT)
#define LAUNCHER_DOWN_RIGHT     (LAUNCHER_DOWN | LAUNCHER_RIGHT)

typedef struct
{
	uint32_t column;
	uint32_t row;
}coordinates;

int find_center(coordinates* coordinates, uint32_t* frame_buffer);
void launcher_cmd(int fd, int cmd);



int main(int argc, char** argv)
{
	int memfd = open("/dev/mem", O_RDWR);
	coordinates coordinate;
	unsigned int duration = 500;
	char *dev = LAUNCHER_NODE;
    	int fd;
	int move_dur;



	uint32_t* frame_buffer = (uint32_t*) mmap(NULL, 1920*1080*2, PROT_READ, MAP_SHARED, memfd, FRAME_BUFFER_ADDRESS);
	if(frame_buffer == MAP_FAILED)
	{
		fprintf(stderr, "Failed to get frame buffer");
		return -1;
	}

	if(argc != 2)
	{
		fprintf(stderr, "... how you mess this up?!?\n");
		return -1;
	}

	move_dur = atoi(argv[1]);

	fd = open(dev, O_RDWR);
	if(fd == -1) {
		perror("Couldn't open file: %m");
		exit(1);
	}

	while(1)
	{
		if(find_center(&coordinate, frame_buffer))
		{
			if(coordinate.column < 430)
			{
				printf("THE ALIEN IS LEFT!\n");
				launcher_cmd(fd, LAUNCHER_LEFT);
				usleep(duration * move_dur);
				launcher_cmd(fd, LAUNCHER_STOP);
			}
			else if(coordinate.column > 530)
			{
				printf("OH NO! HE'S ON THE RIGHT!\n");
				launcher_cmd(fd, LAUNCHER_RIGHT);
				usleep(duration * move_dur);
				launcher_cmd(fd, LAUNCHER_STOP);
			}
			else if(coordinate.row < 760)
			{
				printf("AIM UP GOD DAMN'T!\n");
				launcher_cmd(fd, LAUNCHER_UP);
				usleep(duration * move_dur);
				launcher_cmd(fd, LAUNCHER_STOP);
			}
			else if(coordinate.row > 860)
			{
				printf("IT'S BELOW YOU!\n");
				launcher_cmd(fd, LAUNCHER_DOWN);
				usleep(duration * move_dur);
				launcher_cmd(fd, LAUNCHER_STOP);
			}
			else
			{
				printf("\x1b[31mDIE \"SIGNS 2\" ALIENS, DIE!!!\x1b[0m\n");
				launcher_cmd(fd, LAUNCHER_FIRE);
				usleep(duration * 1000);
				launcher_cmd(fd, LAUNCHER_STOP);
				break;
			}
		}
	}	
	
	close(memfd);

	return 0;
}

void launcher_cmd(int fd, int cmd) {
    int retval = 0;
  
    retval = write(fd, &cmd, 1);
    while (retval != 1) {
        if (retval < 0) {
            fprintf(stderr, "Could not send command to %s (error %d)\n", LAUNCHER_NODE, retval);
        } 

        else if (retval == 0) {
            fprintf(stdout, "Command busy, waiting...\n");
        }

        else
        {
            fprintf(stdout, "... get out!\n");
        }
    }

    if (cmd == LAUNCHER_FIRE) {
        usleep(5000000);
    }
}

int find_center(coordinates* coordinate, uint32_t* frame_buffer)
{
	int i,j;

	uint32_t tmp;
	uint8_t Y;
	uint8_t cB;
	uint8_t cR;
	uint8_t tol, btol;
	uint32_t count_b=0,count_w=0;
	uint8_t state = WAIT;
	uint8_t color;
	uint32_t state_count = 0;

	uint8_t found = 0;
	uint32_t column;
	uint32_t row;
	uint32_t column_temp;
	uint32_t row_temp;

	tol = 10;
	btol = 10;

	for(i=0;i<1080;i++)
	{
		for(j=0;j<1920/2;j++)
		{
			tmp = frame_buffer[i*1920/2 + j];
			Y = (tmp>>24)&0xFF;
			cR = (tmp>>16)&0xFF;
			cB = (tmp&0xFF);

			//black
			if((Y > (130 - 10) && Y < (130 + 10))
				&& (cR > (30 - tol) && cR < (30 + tol))
				&& (cB > (28 - tol) && cB < (28 + tol)))
			{
				count_b++;
				if(count_b >= btol)
				{
					count_w = 0;
					color = BLACK;
					//fprintf(out_file, "2,");
				}
				else
				{	
					color = WHITE;
					//fprintf(out_file, "1,");
				}
			}
			// white
//			if((Y > (137 - 10) && Y < (137 + 10)) 
//				&& (cB > (110 - tol) && cB < (110 + tol))
//				&& (cR > (109 - tol) && cR < (109 + tol)))
			else
			{
				count_w++;
				if(count_w >= 4)
				{
					count_b = 0;
					color = WHITE;
					//fprintf(out_file, "1,");
				}
				else
				{	
					color = BLACK;
					//fprintf(out_file, "2,");
				}
			}

			// color = 1 => white
			// color = 2 => black
			//fprintf(out_file, "%d,", state);
			switch (state)
			{
				case WAIT:
					if (color == BLACK)
						state_count ++;
					else
						state_count = 0;
					if (state_count > 5)
						state = BLACK1;
					break;
				case BLACK1:
					if (color == BLACK)
					{
						state_count ++;
						if (state_count > 20)
						{
							state_count = 0;
							state = WAIT;
						}
					}
					else
					{
						state_count = 0;
						state = WHITE1;
					}
					break;
				case WHITE1:
					if (color == WHITE)
					{
						state_count ++;
						if(state_count > 20)
							state = WHITE1_CONF;
					}					
					else
					{
						state_count = 0;
						state = WAIT;
					}
					break;
				case WHITE1_CONF:
					if (color == WHITE)
					{
						state_count ++;
						if (state_count > 45)
						{
							state_count = 0;
							state = WAIT;
	 					}
					}
					else
					{
						state_count = 0;
						state = BLACK2;
					}
					break;
				case BLACK2:
					if (color == BLACK)
					{
						state_count ++;
						if(state_count > 5)
							state = BLACK2_CONF;
					}					
					else
					{
						state_count = 0;
						state = WAIT;
					}
					break;
				case BLACK2_CONF:
					if (color == BLACK)
					{
						state_count ++;
						if (state_count > 20)
						{
							state_count = 0;
							state = WAIT;
	 					}
					}
					else
					{
						state_count = 0;
						state = WHITE2;
					}
					break;


				case WHITE2:
					if (color == WHITE)
					{
						state_count ++;
						if(state_count > 20)
							state = WHITE2_CONF;
					}					
					else
					{
						state_count = 0;
						state = WAIT;
					}
					break;
				case WHITE2_CONF:
					if (color == WHITE)
					{
						state_count ++;
						if (state_count > 45)
						{
							state_count = 0;
							state = WAIT;
	 					}
					}
					else
					{
						state_count = 0;
						state = BLACK3;
					}
					break;
				case BLACK3:
					if (color == BLACK)
					{
						state_count ++;
						if(state_count > 5)
							state = BLACK3_CONF;
					}					
					else
					{
						state_count = 0;
						state = WAIT;
					}
					break;
				case BLACK3_CONF:
					if (color == BLACK)
					{
						state_count ++;
						if (state_count > 20)
						{
							state_count = 0;
							state = WAIT;
	 					}
					}
					else
					{
						state_count = 0;
						state = WHITE3;
					}
					break;



				case WHITE3:
					if (color == WHITE)
					{
						state_count ++;
						if(state_count > 20)
							state = WHITE3_CONF;
					}					
					else
					{
						state_count = 0;
						state = WAIT;
					}
					break;
				case WHITE3_CONF:
					if (color == WHITE)
					{
						state_count ++;
						if (state_count > 45)
						{
							state_count = 0;
							state = WAIT;
	 					}
					}
					else
					{
						state_count = 0;
						state = TARGET;
					}
					break;


				case TARGET:
					if (color == BLACK)
					{
						state_count ++;
						if(state_count > 45)
						{
							state = TARGET_CONF;
							column_temp = j;
							row_temp = i;
						}					
					}					
					else
					{
						state_count = 0;
						state = WAIT;
					}
					break;
				case TARGET_CONF:
					if (color == BLACK)
					{
						state_count ++;
						if (state_count > 70)
						{
							state_count = 0;
							state = WAIT;
	 					}
					}
					else
					{
						state_count = 0;
						state = WHITE4;
					}
					break;


				case WHITE4:
					if (color == WHITE)
					{
						state_count ++;
						if(state_count > 20)
							state = WHITE4_CONF;
					}					
					else
					{
						state_count = 0;
						state = WAIT;
					}
					break;
				case WHITE4_CONF:
					if (color == WHITE)
					{
						state_count ++;
						if (state_count > 45)
						{
							state_count = 0;
							state = WAIT;
	 					}
					}
					else
					{
						state_count = 0;
						state = BLACK4;
					}
					break;
				case BLACK4:
					if (color == BLACK)
					{
						state_count ++;
						if(state_count > 5)
							state = BLACK4_CONF;
					}					
					else
					{
						state_count = 0;
						state = WAIT;
					}
					break;
				case BLACK4_CONF:
					if (color == BLACK)
					{
						state_count ++;
						if (state_count > 20)
						{
							state_count = 0;
							state = WAIT;
	 					}
					}
					else
					{
						state_count = 0;
						state = WHITE5;
					}
					break;


				case WHITE5:
					if (color == WHITE)
					{
						state_count ++;
						if(state_count > 20)
							state = WHITE5_CONF;
					}					
					else
					{
						state_count = 0;
						state = WAIT;
					}
					break;
				case WHITE5_CONF:
					if (color == WHITE)
					{
						state_count ++;
						if (state_count > 45)
						{
							state_count = 0;
							state = WAIT;
	 					}
					}
					else
					{
						state_count = 0;
						state = BLACK5;
					}
					break;
				case BLACK5:
					if (color == BLACK)
					{
						state_count ++;
						if(state_count > 5)
							state = BLACK5_CONF;
					}					
					else
					{
						state_count = 0;
						state = WAIT;
					}
					break;
				case BLACK5_CONF:
					if (color == BLACK)
					{
						state_count ++;
						if (state_count > 20)
						{
							state_count = 0;
							state = WAIT;
	  					}
					}
					else
					{
						state_count = 0;
						state = WHITE6;
					}
					break;

				case WHITE6:
					if (color == WHITE)
					{
						state_count ++;
						if(state_count > 20)
							state = WHITE6_CONF;
					}					
					else
					{
						state_count = 0;
						state = WAIT;
					}
					break;
				case WHITE6_CONF:
					if (color == WHITE)
					{
						state_count ++;
						if (state_count > 45)
						{
							state_count = 0;
							state = WAIT;
	 					}
					}
					else
					{
						state_count = 0;
						state = BLACK6;
					}
					break;
				case BLACK6:
					if (color == BLACK)
					{
						state_count ++;
						if(state_count > 5)
							state = BLACK6_CONF;
					}					
					else
					{
						state_count = 0;
						state = WAIT;
					}
					break;
				case BLACK6_CONF:
					if (color == BLACK)
					{
						state_count ++;
						if (state_count > 20)
						{
							state_count = 0;
							state = WAIT;
	 					}
					}
					else
					{
						state_count = 0;
						// TARGET CONFIRM!!!!!!!!!!
						found = 1;
						row = row_temp;
						column = column_temp;
						state = WAIT;
					}
					break;

			} // case(state)
		} // for (j)
		//fprintf(out_file,"\n");
	} // for (i)

	//adjust missile launcher
	if(found == 1)
	{
		printf("Coordinates: col = %d row = %d\n", column, row);
		coordinate->column = column;
		coordinate->row = row;
		return 1;
	}

	return 0;
	
	//fclose(out_file);

}
