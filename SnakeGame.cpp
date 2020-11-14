#include "SnakeGame.h"
#include <unistd.h>

using namespace std;


CharPosition::CharPosition(int col, int row)
{
	x = col;
	y = row;
}

CharPosition::CharPosition()
{
	x = 0;
	y = 0;
}

SnakeGame::SnakeGame()
{
	// 변수 초기화
	headchar = (char)229;
	partchar = 'x'; 
	edgechar = (char)64; 
	fruitchar = 'x'; 
	fruit.x = 0;
	fruit.y = 0;
	score = 0;
	//del은 딜레이 1000000이 1초 50만은 0.5초
	del = 200000;
	bool bEatsFruit = 0;
	bool EatsPoison = false;
	direction = 'l';
	srand(time(NULL));
	
	InitGameWindow();
	//maxwidth- 15한 이유는 점수를 오른쪽에 출력해야하는데 그 자리만들라고
	maxwidth-=15;
	PositionFruit();
	DrawWindow();
	DrawSnake();
	PrintScore();

	refresh();	
}

SnakeGame::~SnakeGame()
{
	nodelay(stdscr, false);
	getch();
	
	endwin();
}

// initialise the game window
void SnakeGame::InitGameWindow() 
{ 

	initscr(); // initialise the screen
	
	nodelay(stdscr,TRUE); //
	keypad(stdscr, true); // 방향키를 통해 뱀 이동을 조정할거니 keypad(*win,bool)의 bool true로
	noecho(); // 입출력모드 지정 반향기능을 정지  입력한 값을 화면에 안보이게
	curs_set(0); // 화면에 보이는 커서를 설정, 0은 안보이게, 1은 일반, 2는 큰 커서
	refresh();
	getch();	
		
	//현재 화면의 가로 세로의 크기를 구한다 getmaxyx(win,max_y,max_x) y값의크기와 x의크기를구해 각각 max_y,max_x에 넣음
	//win에 해당하는 stdscr은 표준화면을 의미함 
	getmaxyx(stdscr, maxheight, maxwidth); 
	return; 
}

// 맵 만들기 window 위에다가 **만일 맵을 여러개만든다면 선택변수 추가해가지고 여기 밑에 테두리 그리는것들 중에서 선택하게?
void SnakeGame::DrawWindow()
{
	//뱀새기가 활동할 부분을 테두리로 표기, 이때 Immune Wall은 다른문자로 표기
	for (int i = 0; i < maxwidth; i++) // top
	{
		move(0, i);
		addch(edgechar);
		
	}

	for (int i = 0; i < maxwidth; i++) // bottom
	{	
		move(maxheight-1, i);
		addch(edgechar);
		
	}

	for (int i = 0; i < maxheight; i++) // left side
	{
		move(i, 0);
		if(i==maxheight-1 or i==0){
			addch((char)219);
		}else{
			addch(edgechar);
		}
	}

	for (int i = 0; i < maxheight; i++) // right side
	{
		move(i, maxwidth-1);
		if(i==maxheight-1 or i==0){
			addch((char)219);
		}else{
			addch(edgechar);
		}
	}
	return;
}

// draw snake's body
void SnakeGame::DrawSnake()
{
	for (int i = 0; i < 5; i++) 
	{
		snake.push_back(CharPosition(50+i, 20));
	}
	
	//길이가 몇이든 길이만큼 표시를해야함
	for (int i = 0; i < snake.size(); i++)
	{
		move(snake[i].y, snake[i].x);
		addch(partchar);
		
	}
	return;
}

// 점수표시 우측상단에할거
void SnakeGame::PrintScore()
{
	move(0, maxwidth+1);
	printw("Score: %d", score);
	return;
}

// 화면에 먹이 출력  임의의 위치여야함
void SnakeGame::PositionFruit()
{
	while(1)
	{
		int tmpx = rand()%maxwidth+1; // 1늘린건 0을 피하기위해서  1~maxwidth까지
		int tmpy = rand()%maxheight+1;

		// 뱀 위에는 나타나지않는다
		for (int i = 0; i < snake.size(); i++)
		{
			if (snake[i].x == tmpx && snake[i].y == tmpy)
			{
				continue; // 뱀 위에 나타나는거였으면 밑에 무시하고 다시 루프돌림
			}
		}

		// 맵에 있으면 넘어간다
		if (tmpx >= maxwidth-2 || tmpy >= maxheight-3)
		{
			continue; 
		}

		// 좌표설정되면 맵상에 표시
		fruit.x = tmpx;
		fruit.y = tmpy;
		break;
	}

	move(fruit.y, fruit.x); 
	addch(fruitchar);
	refresh();
}

// set game over situations
bool SnakeGame::FatalCollision()
{
	// 벽에 부딪칠경우
	if (snake[0].x == 0 || snake[0].x == maxwidth-1 || snake[0].y == 0 || snake[0].y == maxheight-2)
	{
		return true;
	}

	
	//자기몸에 부딪친경우
	for (int i = 2; i < snake.size(); i++)
	{
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
		{
			return true;
		}
	}

	return false;
}

//맵상의 fruit먹었을때
bool SnakeGame::GetsFruit()
{	
	//뱀새끼 대가리좌표 snake[0].x , snake[0].y가 fruit의 좌표와 동일하면 먹는상황임
	if (snake[0].x == fruit.x && snake[0].y == fruit.y)
	{	
		//PositionFruit() fruit을 먹었으니 랜덤한 위치에 재생성
		PositionFruit(); 
		score +=50; 
		PrintScore();

		// if score is a multiple of 100, increase snake speed
		if ((score%100) == 0)
		{
			del -= 10000;
		}
		return bEatsFruit = true;
	}
	else 
	{
		return bEatsFruit = false;
	}
	return bEatsFruit;
}


void SnakeGame::MoveSnake()
{	
	//뱀새끼 움직일 방향 결정한다, 키 입력받아서 switch로 case를 나눠 실행, BackSpace시 게임 종료
	int KeyPressed = getch();
		
	switch(KeyPressed)
	{
		case KEY_LEFT:
			if (direction != 'r') 
			{ direction = 'l'; break;}	
			else if(direction == 'r')
			{ direction = 'q'; break;}
		case KEY_RIGHT:
			if (direction != 'l')
			{ direction = 'r'; break;}
			else if(direction == 'l')
			{ direction = 'q'; break;}
		case KEY_UP:
			if (direction != 'd')
			{ direction = 'u'; break;}
			else if(direction == 'd')
			{ direction = 'q'; break;}
		case KEY_DOWN:
			if (direction != 'u')
			{ direction = 'd'; break;}
			else if(direction == 'u')
			{ direction = 'q'; break;}
		case KEY_BACKSPACE:
			direction = 'q'; // key to quit the game
			break;
	}

	// Fruit과 Poison을 둘 다 안먹었을때 size 그대로, 앞으로 전진, 맨뒤제거, 새로운 머리, 예전머리 몸통으로표기
	if (!bEatsFruit)
	{	
		//snake 몸통 vector의 맨 마지막부분을 지우고 vector의 크기도 1줄임
		move(snake[snake.size()-1].y, snake[snake.size()-1].x); // 맨 뒤 요소로 이동
		printw(" "); 
		refresh();
		snake.pop_back();
	
	}
	
	
	// 이동하는 방향에다가 문자를 넣어야
	if (direction == 'l')
	{ snake.insert(snake.begin(), CharPosition(snake[0].x-1, snake[0].y)); } 
	else if (direction == 'r')
	{ snake.insert(snake.begin(), CharPosition(snake[0].x+1, snake[0].y)); }
	else if (direction == 'u')
	{ snake.insert(snake.begin(), CharPosition(snake[0].x, snake[0].y-1)); }
	else if (direction == 'd')
	{ snake.insert(snake.begin(), CharPosition(snake[0].x, snake[0].y+1)); }

	move(snake[0].y, snake[0].x);	
	addch(headchar); // 새로운 머리를 지정
	move(snake[1].y, snake[1].x);
	addch(partchar); // 머리와 몸통의 문자가 다르니까 머리가 이동하고 그 이전 자리를 몸통의 문자로 바꿔줘야함	
	refresh();
	return;
	
	
}

// SnakeGame newGame >> newGame.PlayGame(); 으로 게임 시작
void SnakeGame::PlayGame()
{
    while(1)
    {	//머가리 충돌시, 역방향입력시 게임 종료 가운데에 출력
        if (FatalCollision())
        {
            move((maxheight-2)/2,(maxwidth-5)/2);
            printw("GAME OVER");
            break;
        }
	
        GetsFruit();		//먹었냐안먹었냐 bool 판별한 뒤에 MoveSnake()실행
        MoveSnake();

        if (direction=='q') //exit
        {
		move((maxheight-2)/2,(maxwidth-5)/2);
		printw("GAME OVER");
        	break;
        }
	
	/* 프로그램 속도 조절  usleep메소드는 usleep(int micro_seconds) 따라서 usleep(백만)= 1초 후 다음 작업 실행
	 * 즉, usleep(백만)은 1초의 딜레이를 준다는 것 우리는 0.5초의 틱을 준다면 50만으로 초기설정	 
	 */
	
        usleep(del); // delay, while문이 1번하는데 딜레이 >>GetsFruit()과 MoveSnake()가 딜레이마다 실행
    }
}
