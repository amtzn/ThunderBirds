#include "Menu.h"


void Menu::printEnteryScreen() const
{
	clrscr();

	char arr[][40] = { "WELCOME TO THUNDERBIRDS V3.0!", "WE HOPE YOU'LL ENJOY THE GAME!", "BEST OF LUCK!", "ITAMAR AND AMIT"};

	std::cout << "  .. .,  ,  ,. ,.  ,  .  ,. .,  .  ,. ,.  .  .. ,,  ,  .  ., ..  ./@@@@@@. .  .." << std::endl <<
		",,  ,  .. ,, .,  ,. ,, .,  ,  ,, .,  ,  ,. ,, .,  ,. ,, .@@#.,/##%%%%%#%@*. ,, ." << std::endl <<
		",,  ,  ,. .,  ,  ,. ,. .,  ,  ,, .,  ,  ,. ,. .,  ..%@.   @&%%##%%%%%%%%@.. ,, ." << std::endl <<
		"  ,. .,  ,  ,. ,, .,  ,  ,. .,  ,  .. ,, .,  ,. *@          *@#%#%%%%%%#@  ,  .." << std::endl <<
		"  ,. .,  ,  ,. ,, .,  ,. ,. .,  ,  ,. ,,  ,  /@                @&%%%%%%@.  ,  ,." << std::endl <<
		",,  ,  .. .,  ,  ,. ,. .,  .  ,, .,  ,  ,. @.                    (@#%%&/ ,. ,, ." << std::endl <<
		",,  ,  ,. .,  ,  ,. ,, .,  ,  ., ..  .  ,@         .     ..        .@@#  ,. ,, ." << std::endl <<
		" ... .. ..  .. ..  .  .. .. .. ..  /* .@        ..        .,        &. .. ..  .." << std::endl <<
		"  ,. ,,  ,  ,. ,, .,  ,  ,. ..@&%%%%#&.          ,        ..   . , @,, ,,  ,  , " << std::endl <<
		"...... ....................&%%%%%&%&%             ..    ..  . .,.@,. .. ... ...." << std::endl <<
		",,  ,  .. .,  ,  ,  ,. .,@%%&&., .&. .         .           .,,.@* .,  ,  ,. ,, ." << std::endl <<
		".......................@%@,......@/&       &&@/.        ,,.,.@.................." << std::endl <<
		"  ,. ,,  ,  ,. ,, ., @@. .. .,  @.,*,@, ,@%@,,,,    .,,,,.@/ ..  ,  ,, ,, .,  , " << std::endl <<
		"  .. .. ..  .. .. .. ... .. .....&(***@%@,..,..,,.,,...@, .. ..  .  .. .. ..  .." << std::endl <<
		",.  ,  ,. ,,  ,  ,. ,. .,  ,.*(/,. (@%&***@,,,.,,..@&&/ .,  ,  ,. .,  ,  ,. ,, ." << std::endl <<
		"..  .  .. .. .,  ,. ,. .. ,(//, .@%@,,&#////&&(@&%%%%%# .,  .  ,. ..  ,  ,. ,. ." << std::endl <<
		"  ,. .,  ,  ,. ,. .,  ,.#(/*.,#&&%,,,/(,,@&  ,. #%#%%& .  ,. .,  ,  ,, ,,  ,  ,." << std::endl <<
		"  ,. .,  ,  ,. ,, .,  /#//,/*,%*,,,/( ,.  ,  ..@##%@.  ,  ,. .,  ,  ., .,  ,  ,." << std::endl <<
		",.  ,  .. .,  ,  ,  ,(////*,//,,//(,.,  .. ,,@%#&&,. ,, .,  .  ,. .,  ,  ,. ,, ." << std::endl <<
		",,  ,  .. ., .,  ,,(*(((//(#*//##.,  ,  .. &#&@,  ,. ,. .,  ,  ,. .,  ,  ,. ,, ." << std::endl <<
		"  ,. ,,  ,  ,. ,#((/((*(/(/(##. ,  .. ,, @@* ,. ,,  ,  ,  ,. .,  ,  ,, ,,  .  ,." << std::endl <<
		"  ,. ,,  ,  ,##*,.#//(.((## ..  .  ,. ,, .,  ,. ,, .,  ,  ,. .,  .  ,, .,  ,  ,." << std::endl <<
		",,  ,  ,#...  .,((/ .((#.  ,  ,, .,  ,  ,. ,. .,  ,. ,, .,  ,  ,, .,  ,  ,. ,, ." << std::endl <<
		",,  ,  .. ,, (#* ,  #* .,  .  ,, .,  ,  ,. ,, .,  ,. ,, .,  ,  ,. .,  ,  ,. ,, ." << std::endl <<
		"  ,. ,,  , #,. ,, #.  ,  ,. .,  ,  ,. ,,  ,  ,. ,, .,  ,  ,. ,,  ,  ,, ,, .,  ,.";
									
	Sleep(400);

	for (int i = 0; i < 4; i++)
	{
		int len = strlen(arr[i]);
		for (int j = 0; j < len; j++)
		{
			gotoxy(5 + j, 1 + i);
			std::cout << arr[i][j];
			Sleep(80);
		}
		Sleep(600);
	}

	Sleep(1000);
}

void Menu::printMenu() const
{
	clrscr();
	std::cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" << std::endl <<
		"W                                                                              W" << std::endl <<
		"W                                                                              W" << std::endl <<
		"W                                                                              W" << std::endl <<
		"W                                                                              W" << std::endl <<
		"W                   WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW                   W" << std::endl <<
		"W                   W     WELCOME TO THUNDERBIRDS V3.0     W                   W" << std::endl <<
		"W                   WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW                   W" << std::endl <<
		"W                   W     (1) START NEW GAME               W                   W" << std::endl <<
		"W                   WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW                   W" << std::endl <<
		"W                   W     (2) START NO COLOR GAME          W                   W" << std::endl <<
		"W                   WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW                   W" << std::endl <<
		"W                   W     (3) RUN SINGLE BOARD             W                   W" << std::endl <<
		"W                   WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW                   W" << std::endl <<
		"W                   W     (4) RUN NO COLOR SINGLE BOARD    W                   W" << std::endl <<
		"W                   WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW                   W" << std::endl <<
		"W                   W     (8) INSTRUCTIONS AND KEYS        W                   W" << std::endl <<
		"W                   WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW                   W" << std::endl <<
		"W                   W     (9) EXIT                         W                   W" << std::endl <<
		"W                   WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW                   W" << std::endl <<
		"W                                                                              W" << std::endl <<
		"W                                                                              W" << std::endl <<
		"W                                                                              W" << std::endl <<
		"W                                                                              W" << std::endl <<
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW";
}

void Menu::printKeysAndInst() const
{
	clrscr();

	std::cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" << std::endl <<
		"W                                                                              W" << std::endl <<
		"W       Instructions and Keys                                                  W" << std::endl <<
		"W                                                                              W" << std::endl <<
		"W       Key  Operation                                                         W" << std::endl <<
		"W                                                                              W" << std::endl <<
		"W       B/b: Switching to BIG SpaceShip                                        W" << std::endl <<
		"W       S/s: Switching to SMALL SpaceShip                                      W" << std::endl <<
		"W       W/w: UP                                                                W" << std::endl <<
		"W       X/x: DOWN                                                              W" << std::endl <<
		"W       A/a: LEFT                                                              W" << std::endl <<
		"W       D/d: RIGHT                                                             W" << std::endl <<
		"W       ESC --> ESC: Pause and then continue                                   W" << std::endl <<
		"W       ESC --> 9: Pause and exit game                                         W" << std::endl <<
		"W                                                                              W" << std::endl <<
		"W                                                                              W" << std::endl <<
		"W                                                                              W" << std::endl <<
		"W                                                                              W" << std::endl <<
		"W       PRESS ESC TO RETURN TO MENU                                            W" << std::endl <<
		"W                                                                              W" << std::endl <<
		"W                                                                              W" << std::endl <<
		"W                                                                              W" << std::endl <<
		"W                                                                              W" << std::endl <<
		"W                                                                              W" << std::endl <<
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW";
}

void Menu::printExit() const
{
	clrscr();
	std::cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" << std::endl <<
		"W                                                                              W" << std::endl << 
		"W      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%       W" << std::endl <<
		"W      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%       W" << std::endl <<
		"W      @@@@                                                         @@@%       W" << std::endl <<
		"W      @@@@     #@@@@@@@@@@& /@@@@    (@@@&  @@@@( .@@@@@@@@@@@#    @@@%       W" << std::endl <<
		"W      @@@@     #@@@@@@@@@@&  /@@@@  (@@@&   @@@@( .@@@@@@@@@@@#    @@@%       W" << std::endl <<
		"W      @@@@     #@@@@          /@@@% @@@@    @@@@(     #@@@@        @@@%       W" << std::endl <<
		"W      @@@@     #@@@@           #@@@@@@@     @@@@(     #@@@@        @@@%       W" << std::endl <<
		"W      @@@@     #@@@@@@@@&       &@@@@@      @@@@(     #@@@&        @@@%       W" << std::endl <<
		"W      @@@@     #@@@@@@@@&       &@@@@@      @@@@(     #@@@@        @@@%       W" << std::endl <<
		"W      @@@@     #@@@@           #@@@@@@@     @@@@(     #@@@@        @@@%       W" << std::endl <<
		"W      @@@@     #@@@@          (@@@% @@@@    @@@@(     #@@@&        @@@%       W" << std::endl <<
		"W      @@@@     #@@@@@@@@@@&  /@@@@  ,@@@@   @@@@(     #@@@@        @@@%       W" << std::endl <<
		"W      @@@@     #@@@@@@@@@@& ,@@@@    &@@@@  @@@@(     #@@@@        @@@%       W" << std::endl <<
		"W      @@@@                                                         @@@%       W" << std::endl <<
		"W      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%       W" << std::endl <<
		"W      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%       W" << std::endl <<
		"W                                                                              W" << std::endl <<
		"W      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@       W" << std::endl <<
		"W      @                                                               @       W" << std::endl <<
		"W      @                                                               @       W" << std::endl <<
		"W      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@       W" << std::endl <<
		"W                                                                              W" << std::endl <<
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW";

	for (int i = 0; i < ExitScreen::BarWidth; i++)
	{
		gotoxy(ExitScreen::InitCol + i, ExitScreen::UpRow);
		std::cout << ExitScreen::BarFigure;
		gotoxy(ExitScreen::InitCol + i, ExitScreen::DownRow);
		std::cout << ExitScreen::BarFigure;

		Sleep(30);
	}
	clrscr();
}


