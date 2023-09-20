#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <time.h>

using namespace sf;
using namespace std;

#define velocityx 0.6
#define endl '\n'

struct players
{
	Texture playertex;
	Sprite players;
	bool chosen = 0;
};

struct shields
{
	Sprite shields;
	bool touched = 0;
};

void Rand_Gen_Of_pipes(int arr[]);
void initialization_of_pipes(Sprite arrup[], Sprite arrdown[], int pos_arr[], Texture& pipe,int diff);
void set_shield_arr(shields arrofshields[], Texture& shield, Sprite arrup[], Sprite arrdown[],int& shieldcntr);
void Initialize_background(RectangleShape arrback[], RectangleShape arrbase[], Texture& levelback, Texture& levelbase);
void check_pipe_collision(bool& collide, Sprite player1s, Sprite arrup[], Sprite arrdown[]);
void check_base_collision(bool& collide, Sprite player1s, RectangleShape arrofbase[]);
void collide_animation(Sprite& player1s, players arrofplayers[], RectangleShape arrofbase[], double& velocityy, bool touchedground);


const int PIPES = 100;



int main() {
	RenderWindow window(sf::VideoMode(1200, 700), "Flappy bird");


	Texture back, start, skin, levelback, player1, levelbase, credit, backbutton, pausebutton, blank, pipe, shield, shieldcircle, info, gameover,difficulty, easy,hard, okay,diffarrow;

	Sprite backs, starts, skins, levelbacks,  player1s, levelbases, credits, backbuttons, pausebuttons, blanks, shieldcircles, infos, gameovers, difficultys, easys, hards, okays, diffarrows;

	shields arrofshields[5];
	players arrofplayers[6];

	back.loadFromFile("back.jpeg");
	start.loadFromFile("start.png");
	skin.loadFromFile("skin.png");
	levelback.loadFromFile("levelback2.png");
	player1.loadFromFile("flappysprite.png");
	arrofplayers[0].playertex.loadFromFile("flappysprite.png");
	arrofplayers[0].chosen = 1;
	arrofplayers[1].playertex.loadFromFile("player2.png");
	arrofplayers[2].playertex.loadFromFile("player3.png");
	arrofplayers[3].playertex.loadFromFile("player4.png");
	arrofplayers[4].playertex.loadFromFile("player5.png");
	arrofplayers[5].playertex.loadFromFile("player6.png");

	credit.loadFromFile("credit.png");
	levelbase.loadFromFile("levelbase.png");
	backbutton.loadFromFile("backbutton.png");
	blank.loadFromFile("blank.png");
	pipe.loadFromFile("pipe.png");
	pausebutton.loadFromFile("pausebutton.png");
	shield.loadFromFile("shield.png");
	shieldcircle.loadFromFile("shield circle.png");
	info.loadFromFile("info.png");
	gameover.loadFromFile("gameover.png");
	difficulty.loadFromFile("difficulty.png");
	easy.loadFromFile("easy.png");
	hard.loadFromFile("hard.png");
	okay.loadFromFile("okay.png");
	diffarrow.loadFromFile("diffarrow.png");


	Font foont, foont2, scoefont, originalfont;
	foont2.loadFromFile("blackish.ttf");
	foont.loadFromFile("gadalahfont.ttf");
	scoefont.loadFromFile("Ranika.otf");
	originalfont.loadFromFile("FlappyBirdy.ttf");

	difficultys.setTexture(difficulty);
	difficultys.setScale(0.5, 0.5);
	difficultys.setPosition(470, 470);

	easys.setTexture(easy);
	easys.setScale(0.7, 0.7);
	easys.setPosition(200, 330);

	hards.setTexture(hard);
	hards.setScale(0.7, 0.7);
	hards.setPosition(800, 330);

	okays.setTexture(okay);
	okays.setScale(0.7, 0.7);
	okays.setPosition(500, 330);

	diffarrows.setTexture(diffarrow);
	diffarrows.setScale(0.5, 0.5);
	diffarrows.setPosition(easys.getPosition().x+40, easys.getPosition().y + 80);

	Music music;


	SoundBuffer hitb, scoreb,congb;
	hitb.loadFromFile("hit.wav");
	scoreb.loadFromFile("score.wav");
	congb.loadFromFile("cong sound.wav");
	Sound hit, scorep,cong;
	cong.setBuffer(congb);
	hit.setBuffer(hitb);
	scorep.setBuffer(scoreb);

	Text score, mxscore, shieldtxt,pausetxt,presR;
	score.setFont(scoefont);
	score.setCharacterSize(30);
	score.setPosition(1050, 0);
	score.setFillColor(Color::White);
	score.setStyle(Text::Bold);


	pausetxt.setFont(originalfont);
	pausetxt.setString("paused");
	pausetxt.setCharacterSize(100);
	pausetxt.setPosition(65, 400);
	pausetxt.setFillColor(Color::White);

	presR.setFont(originalfont);
	presR.setString("press R to resume");
	presR.setCharacterSize(100);
	presR.setPosition(65, 400);
	presR.setFillColor(Color::White);

	mxscore.setFont(scoefont);
	mxscore.setCharacterSize(30);
	mxscore.setPosition(900, 50);
	mxscore.setFillColor(Color::White);
	mxscore.setStyle(Text::Bold);

	shieldtxt.setFont(scoefont);
	shieldtxt.setCharacterSize(30);
	shieldtxt.setPosition(250, 50);
	shieldtxt.setFillColor(Color::White);
	shieldtxt.setStyle(Text::Bold);

	

	pausebuttons.setTexture(pausebutton);
	pausebuttons.setPosition(15, 15);
	pausebuttons.setScale(0.061, 0.061);



	levelbases.setTexture(levelbase);

	blanks.setTexture(blank);
	blanks.setScale(1.5, 1.5);

	backbuttons.setTexture(backbutton);
	backbuttons.setPosition(15, 15);
	backbuttons.setScale(0.061, 0.061);

	backs.setTexture(back);
	backs.setScale(1.25, 1.25);

	infos.setTexture(info);
	infos.setPosition(1120, 595);
	infos.setScale(0.08, 0.08);

	starts.setTexture(start);
	starts.setPosition(500, 350);
	starts.setScale(0.5, 0.5);

	skins.setTexture(skin);
	skins.setScale(0.5, 0.5);
	skins.setPosition(510, 430);

	credits.setTexture(credit);
	credits.setScale(0.04, 0.04);
	credits.setPosition(0, 620);

	levelbacks.setTexture(levelback);
	levelbacks.setScale(1.33, 1.33);

	arrofplayers[0].players.setTexture(arrofplayers[0].playertex);
	arrofplayers[1].players.setTexture(arrofplayers[1].playertex);
	arrofplayers[2].players.setTexture(arrofplayers[2].playertex);
	arrofplayers[3].players.setTexture(arrofplayers[3].playertex);
	arrofplayers[4].players.setTexture(arrofplayers[4].playertex);
	arrofplayers[5].players.setTexture(arrofplayers[5].playertex);


	arrofplayers[0].players.setTextureRect(IntRect(0, 0, 34, 24));
	arrofplayers[0].players.setScale(2, 2);
	arrofplayers[0].players.setPosition(560, 132);

	arrofplayers[1].players.setTextureRect(IntRect(0, 0, 599, 396));
	arrofplayers[1].players.setScale(0.14, 0.14);
	arrofplayers[1].players.setPosition(560, 260);

	arrofplayers[2].players.setTextureRect(IntRect(0, 0, 717, 610));
	arrofplayers[2].players.setScale(0.15, 0.15);
	arrofplayers[2].players.setPosition(560, 388);

	arrofplayers[3].players.setTextureRect(IntRect(0, 0, 1072, 842));
	arrofplayers[3].players.setScale(0.11, 0.11);
	arrofplayers[3].players.setPosition(560, 388);

	arrofplayers[4].players.setTextureRect(IntRect(0, 0, 760, 603));
	arrofplayers[4].players.setScale(0.15, 0.15);
	arrofplayers[4].players.setPosition(560, 388);

	arrofplayers[5].players.setTextureRect(IntRect(0, 0, 1100, 868));
	arrofplayers[5].players.setScale(0.07, 0.07);
	arrofplayers[5].players.setPosition(560, 388);

	player1s.setTexture(player1);
	player1s.setScale(2, 2);
	player1s.setPosition(200, 200);
	player1s.setTextureRect(IntRect(0, 0, 34, 24));

	gameovers.setTexture(gameover);
	gameovers.setPosition(1050, 150);
	gameovers.setScale(2, 2);


	Text keym;
	keym.setString("Press M to return to Main Menu");
	keym.setFont(foont);
	keym.setPosition(1000, 250);
	keym.setCharacterSize(60);
	keym.setFillColor(Color::White);


	shieldcircles.setTexture(shieldcircle);
	shieldcircles.setPosition(550, 115);
	shieldcircles.setScale(0.09, 0.09);



	int level_cnt = 0, charachter = 0, arrpipes[100], scores = 0, x = 0, mxscores = 0, doublepowcntr = 0, shieldpowcntr = 0,diff=1000,tmp=0;
	double velocityy = 0;
	bool first_press = 0, paused = 0, collide = 0, firstcollide = 0, touchedground = 0, first_score_cnt = 0, shieldpow = 0, doublepow = 0, muted = 0, win = 0,changed=1,first_play=0;

	// camera view initialization............
	View camera(FloatRect(0, 0, 1200, 700));


	RectangleShape arrlevelback[PIPES], arrofbase[PIPES];
	Sprite pipeup[PIPES], pipedown[PIPES];

	while (window.isOpen())
	{
		window.setView(camera);


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}

		//mouse position.................

		Vector2i start_index;
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			start_index = Mouse::getPosition(window);

		}

		//levels..........

		if (level_cnt == 0)
		{
			window.clear();

			window.draw(backs);
			window.draw(starts);
			window.draw(skins);
			window.draw(credits);
			window.draw(infos);
			window.draw(difficultys);

			if (paused || collide || win)
			{
				camera.reset(FloatRect(0, 0, 1200, 700));
				window.setView(camera);


				player1s.setScale(2, 2);
				player1s.setPosition(200, 200);

				arrofplayers[0].players.setScale(2, 2);
				arrofplayers[1].players.setScale(0.14, 0.14);
				arrofplayers[2].players.setScale(0.15, 0.15);
				arrofplayers[3].players.setScale(0.11, 0.11);
				arrofplayers[4].players.setScale(0.15, 0.15);
				arrofplayers[5].players.setScale(0.07, 0.07);





				shieldcircles.setPosition(190, 180);
				collide = first_press = firstcollide = touchedground = paused = win =first_play= 0;
				scores = 0;
				score.setPosition(1050, 0);
				mxscore.setPosition(900, 50);
				shieldtxt.setPosition(450, 30);


				window.setView(camera);

			}

			//random pipes.......................

			Rand_Gen_Of_pipes(arrpipes);

			//intitialization of pipes...

			initialization_of_pipes(pipeup, pipedown, arrpipes, pipe,diff);


			//setting arrofshields things...................

			set_shield_arr(arrofshields, shield, pipeup, pipedown,shieldpowcntr);

			//initializing background.....

			Initialize_background(arrlevelback, arrofbase, levelback, levelbase);

			
			//level 1.....
			if (start_index.x > 517 && start_index.x < 670 && start_index.y > 353 && start_index.y < 420) {

				level_cnt = 1;
				music.openFromFile("song.wav");
				music.play();
				music.setVolume(50);
				arrofplayers[1].players.setScale(0.17, 0.17);
				arrofplayers[2].players.setScale(0.12, 0.12);
				arrofplayers[3].players.setScale(0.09, 0.09);
				arrofplayers[4].players.setScale(0.13, 0.13);
				arrofplayers[5].players.setScale(0.08, 0.08);

				for (int i = 0; i < 6; i++)
				{
					arrofplayers[i].players.setPosition(200, 200);
				}
				shieldcircles.setPosition(190, 180);


			}
			//skins......
			else if (start_index.x > 520 && start_index.x < 660 && start_index.y > 440 && start_index.y < 490) {
				
				arrofplayers[0].players.setPosition(100, 85);
				arrofplayers[0].players.setScale(2, 2);
				
				arrofplayers[1].players.setPosition(550, 85);
				arrofplayers[1].players.setScale(0.2, 0.2);

				arrofplayers[2].players.setPosition(1000, 80);
				arrofplayers[2].players.setScale(0.15, 0.15);

				arrofplayers[3].players.setPosition(90, 300);
				arrofplayers[3].players.setScale(0.11, 0.11);

				arrofplayers[4].players.setPosition(550, 300);
				arrofplayers[4].players.setScale(0.15, 0.15);

				arrofplayers[5].players.setPosition(1000, 300);
				arrofplayers[5].players.setScale(0.09, 0.09);
				for (int i = 0; i < 6; i++)
				{
					if (arrofplayers[i].chosen == 1)
						shieldcircles.setPosition(arrofplayers[0].players.getPosition().x +25, arrofplayers[0].players.getPosition().y - 15);

				}

				level_cnt = 2;


			}
			//credits....
			else if (start_index.x > 11 && start_index.x < 127 && start_index.y > 626 && start_index.y < 666) {
				window.clear();
				level_cnt = 3;
			}
			//info........
			else if (start_index.x > 1118 && start_index.x < 1157 && start_index.y > 601 && start_index.y < 676) {

				level_cnt = 4;
			}
			//diff.....
			else if (start_index.x >= 515 && start_index.x <= 668 && start_index.y > 504 && start_index.y < 565)
			{
				level_cnt = 5;
			}
			

		}
		else if (level_cnt == 1)
		{
			window.clear();


			//background....
			for (int i = 0; i < PIPES; i++) {

				window.draw(arrlevelback[i]);
				window.draw(arrofbase[i]);

			}

			//pipes....

			for (int i = 0; i < PIPES; i++) {

				window.draw(pipeup[i]);
				window.draw(pipedown[i]);
			}

			// pipes collision ....................

			if (!shieldpow)
				check_pipe_collision(collide, player1s, pipeup, pipedown);


			//base collision......

			check_base_collision(collide, player1s, arrofbase);

			if (collide && !firstcollide)
			{
				hit.play();
				music.stop();
				firstcollide = 1;
			}

			Vector2f birdposition = player1s.getPosition();

			//collide animation.....

			if (collide) {

				collide_animation(player1s, arrofplayers, arrofbase, velocityy, touchedground);

				// print gameover image........

				gameovers.setPosition(birdposition.x + 200, 150);
				keym.setPosition(birdposition.x + 150, 250);

				window.draw(gameovers);
				window.draw(keym);

				if (Keyboard::isKeyPressed(Keyboard::M))
					level_cnt = 0;
			}

			//scoring ...........


			for (int i = 0; i < PIPES; i++) {
				if (birdposition.x > 900 && (int(birdposition.x) % (diff) - 900 % (diff)) % (diff) == 0)
				{
					if (!first_score_cnt) {
						scores++;
						if (shieldpow) shieldpowcntr++;
						mxscores = max(mxscores, scores);
						scorep.setVolume(50);
						if(diff!=350)
							scorep.play();
					}
					first_score_cnt = 1;
					break;

				}
				first_score_cnt = 0;


			}

			//window.draw(player1s);

			for (int i = 0; i < 6; i++)
			{
				if (arrofplayers[i].chosen == 1)
					window.draw(arrofplayers[i].players);
			}


			//power up drawing..........................

			for (int i = 0; i < 5; i++)
			{
				if (!arrofshields[i].touched)
					window.draw(arrofshields[i].shields);

			}



			score.setString("score:" + to_string(scores));
			mxscore.setString("Highest score:" + to_string(mxscores));
			shieldtxt.setString("shield is applied for " + to_string(4 - shieldpowcntr));

			window.draw(score);
			window.draw(mxscore);
			if (shieldpow) {
				window.draw(shieldtxt);
				window.draw(shieldcircles);
			}


			// activating shields.....
			for (int i = 0; i < 5; i++)
			{
				if (player1s.getGlobalBounds().intersects(arrofshields[i].shields.getGlobalBounds()))
				{
					arrofshields[i].touched = 1;
					shieldpow = 1;
					shieldpowcntr = 0;
				}
			}

			if (shieldpow && 5 - shieldpowcntr % 6 == 1) {
				shieldpow = 0;
			}





			if (Keyboard::isKeyPressed(Keyboard::P))
			{
				paused = 1;
				pausetxt.setPosition(player1s.getPosition().x + 280, 150);
				presR.setPosition(player1s.getPosition().x + 140, 280);
				music.stop();
				//window.draw(keym);
			}
			else if (Keyboard::isKeyPressed(Keyboard::R))
			{		paused = 0;
					music.play();
			}
			if (Keyboard::isKeyPressed(Keyboard::Space))
				first_press = 1;

			if (first_press && !collide)
			{
				if (Keyboard::isKeyPressed(Keyboard::Space) && (player1s.getPosition().y >= 40)) {
					
					player1s.setTextureRect(IntRect(x * 34, 0, 34, 24));
					
					arrofplayers[0].players.setTextureRect(IntRect(x * 34, 0, 34, 24));
					arrofplayers[1].players.setTextureRect(IntRect(x * 599, 0, 599, 396));
					arrofplayers[2].players.setTextureRect(IntRect(x * 716, 0, 717, 610));
					arrofplayers[3].players.setTextureRect(IntRect(x * 1072, 0, 1072, 842));
					arrofplayers[4].players.setTextureRect(IntRect(x * 760, 0, 760, 603));
					arrofplayers[5].players.setTextureRect(IntRect(x * 1100, 0, 1100, 868));

					x++;
					x %= 3;
					velocityy = -0.6;
				}

				// winning the game
				if ((scores==25 && diff==1000)||(scores==30 && diff==750)||(scores==50 && diff==350)) {
					win = 1;

					Text Congratulations;
					Congratulations.setFont(originalfont);
					Congratulations.setString("Congratulations");
					Congratulations.setCharacterSize(100);
					Congratulations.setPosition(65, 400);
					Congratulations.setFillColor(Color::White);
					if (!first_play)
					{
						music.stop();
						cong.play();
					}
					first_play = 1;

					Congratulations.setPosition(birdposition.x + 200, 150);
					keym.setPosition(birdposition.x + 150, 250);

					window.draw(Congratulations);
					window.draw(keym);

				}

				if (!paused && !win) {

					for (int i = 0; i < 6; i++)
					{
						arrofplayers[i].players.move(velocityx, velocityy);
					}
					player1s.move(velocityx, velocityy);
					shieldcircles.move(velocityx, velocityy);
					camera.move(velocityx, 0);
					score.move(velocityx, 0);
					mxscore.move(velocityx, 0);
					shieldtxt.move(velocityx, 0);
					
					velocityy += 0.003;

				}
			}
			if (paused)
			{
				window.draw(pausetxt);
				window.draw(presR);
				//window.draw(keym);
				if (Keyboard::isKeyPressed(Keyboard::M))
					level_cnt = 0;
			}

			if (win)
			{
				if (Keyboard::isKeyPressed(Keyboard::M))
					level_cnt = 0;

			}
		}
		else if (level_cnt == 2)
		{
			window.clear();

			//backgrounds.....
			window.draw(blanks);

			window.draw(backbuttons);
			Text p1, p2, p3, p4, p5, p6;


			if (Mouse::isButtonPressed(Mouse::Left) && start_index.x >= 20 && start_index.x <= 62 && start_index.y >= 19 && start_index.y <= 63)
				level_cnt = 0;


			for (int i = 0; i < 6; i++)
				window.draw(arrofplayers[i].players);
			
			string arrofnames[] = { "Original Flappy" ,"Blue Flappy" ,"Boss Flappy" ,"Scary Flappy" ,"Angry Flappy" ,"Cutie Flappy" };
			Text arroftext[6];

			for (int i = 0;i < 6; i++)
			{
				arroftext[i].setFont(foont2);
				arroftext[i].setString(arrofnames[i]);
				arroftext[i].setCharacterSize(35);
				arroftext[i].setFillColor(Color::Black);
			}


			arroftext[0].setPosition(50, 180);
			arroftext[1].setPosition(550, 180);
			arroftext[2].setPosition(1000, 180);
			arroftext[3].setPosition(65, 400);
			arroftext[4].setPosition(550, 400);
			arroftext[5].setPosition(1000, 400);
			

			for (int i = 0; i < 6; i++)
			{
				window.draw(arroftext[i]);
			}
			
			if (start_index.x >= 100 && start_index.x <= 170 && start_index.y >= 85 && start_index.y <= 130 || arrofplayers[0].chosen == 1)
			{
				arrofplayers[0].chosen = 1;
				arrofplayers[1].chosen = 0;
				arrofplayers[2].chosen = 0;
				arrofplayers[3].chosen = 0;
				arrofplayers[4].chosen = 0;
				arrofplayers[5].chosen = 0;
				window.draw(shieldcircles);
				shieldcircles.setPosition(arrofplayers[0].players.getPosition().x - 15, arrofplayers[0].players.getPosition().y - 15);
				shieldcircles.setScale(0.09, 0.09);

				

			}
			if (start_index.x >= 550 && start_index.x <= 660 && start_index.y >= 85 && start_index.y <= 160 || arrofplayers[1].chosen == 1)
			{
				arrofplayers[0].chosen = 0;
				arrofplayers[1].chosen = 1;
				arrofplayers[2].chosen = 0;
				arrofplayers[3].chosen = 0;
				arrofplayers[4].chosen = 0;
				arrofplayers[5].chosen = 0;
				window.draw(shieldcircles);
				shieldcircles.setPosition(arrofplayers[1].players.getPosition().x - 4, arrofplayers[1].players.getPosition().y - 15);
				shieldcircles.setScale(0.11, 0.11);

			}
			if (start_index.x >= 1000 && start_index.x <= 1100 && start_index.y >= 80 && start_index.y <= 160 || arrofplayers[2].chosen == 1)
			{
				arrofplayers[0].chosen = 0;
				arrofplayers[1].chosen = 0;
				arrofplayers[2].chosen = 1;
				arrofplayers[3].chosen = 0;
				arrofplayers[4].chosen = 0;
				arrofplayers[5].chosen = 0;
				window.draw(shieldcircles);
				shieldcircles.setPosition(arrofplayers[2].players.getPosition().x - 5, arrofplayers[2].players.getPosition().y - 10);
				shieldcircles.setScale(0.12, 0.12);

			}
			if (start_index.x >= 90 && start_index.x <= 190 && start_index.y >= 300 && start_index.y <= 380 || arrofplayers[3].chosen == 1)
			{
				arrofplayers[0].chosen = 0;
				arrofplayers[1].chosen = 0;
				arrofplayers[2].chosen = 0;
				arrofplayers[3].chosen = 1;
				arrofplayers[4].chosen = 0;
				arrofplayers[5].chosen = 0;
				window.draw(shieldcircles);
				shieldcircles.setPosition(arrofplayers[3].players.getPosition().x - 5, arrofplayers[3].players.getPosition().y - 10);
				shieldcircles.setScale(0.12, 0.12);

			}
			if (start_index.x >= 550 && start_index.x <= 660 && start_index.y >= 300 && start_index.y <= 380  || arrofplayers[4].chosen == 1)
			{
				arrofplayers[0].chosen = 0;
				arrofplayers[1].chosen = 0;
				arrofplayers[2].chosen = 0;
				arrofplayers[3].chosen = 0;
				arrofplayers[4].chosen = 1;
				arrofplayers[5].chosen = 0;
				window.draw(shieldcircles);
				shieldcircles.setPosition(arrofplayers[4].players.getPosition().x - 4, arrofplayers[4].players.getPosition().y - 15);
				shieldcircles.setScale(0.11, 0.11);

			}
			if (start_index.x >= 1000 && start_index.x <= 1100 && start_index.y >= 300 && start_index.y <= 380 || arrofplayers[5].chosen == 1)
			{
				arrofplayers[0].chosen = 0;
				arrofplayers[1].chosen = 0;
				arrofplayers[2].chosen = 0;
				arrofplayers[3].chosen = 0;
				arrofplayers[4].chosen = 0;
				arrofplayers[5].chosen = 1;
				window.draw(shieldcircles);
				shieldcircles.setPosition(arrofplayers[5].players.getPosition().x - 5, arrofplayers[5].players.getPosition().y - 10);
				shieldcircles.setScale(0.12, 0.12);

			}
			//**********************************************************************************************************************************


		}
		else if (level_cnt == 3)
		{
			window.clear();
			window.draw(blanks);
			window.draw(backbuttons);



			if (Mouse::isButtonPressed(Mouse::Left) && start_index.x >= 20 && start_index.x <= 62 && start_index.y >= 19 && start_index.y <= 63)
				level_cnt = 0;

			Text arroftext[7];
			string arrofnames[] = { "Team members" ,"Mohamed Hany","Mostafa Mokhtar","Ali Afify","Ammar Thabet", "Omar Alaa" ,"Ali Gadalah" };
			arroftext[0].setFont(foont2);
			arroftext[0].setString(arrofnames[0]);
			arroftext[0].setCharacterSize(100);
			arroftext[0].setPosition(400, 10);
			arroftext[0].setFillColor(Color::Black);

			for (int i = 1; i < 7; i++)
			{
				arroftext[i].setFont(foont);
				arroftext[i].setString(arrofnames[i]);
				arroftext[i].setCharacterSize(80);
				arroftext[i].setFillColor(Color::Black);
			}

			for (int i = 1; i < 4; i++)
				arroftext[i].setPosition(50, 100 + 75 * (i - 1));

			for (int i = 4; i < 7; i++)
				arroftext[i].setPosition(800, 100 + 75 * (i - 4));

			for (int i = 0; i < 7; i++)
				window.draw(arroftext[i]);


		}
		else if (level_cnt == 4)
		{
			window.clear();

			//backgrounds.....
			window.draw(blanks);

			window.draw(backbuttons);

			if (Mouse::isButtonPressed(Mouse::Left) && start_index.x >= 20 && start_index.x <= 62 && start_index.y >= 19 && start_index.y <= 63)
				level_cnt = 0;



			string arrofstrings[] = { "How to play" ,"Controls","Click the Start Button to play","Fly the bird as far as you can without hitting a pipe",
									"Press the spacebar to make the bird jump" ,"Press the P Button to pause the game" ,"Press the R Button to resume the game" };
			Text arroftext[7];

			for (int i = 0; i < 2; i++)
			{
				arroftext[i].setFont(foont2);
				arroftext[i].setCharacterSize(100);
				arroftext[i].setString(arrofstrings[i]);
				arroftext[i].setFillColor(Color::Black);
				arroftext[i].setStyle(Text::Bold);
				arroftext[i].setPosition(400, 10 + 240 * i);
			}

			for (int i = 2; i < 7; i++)
			{
				arroftext[i].setFont(foont);
				arroftext[i].setCharacterSize(50);
				arroftext[i].setString(arrofstrings[i]);
				arroftext[i].setFillColor(Color::Blue);
				arroftext[i].setStyle(Text::Bold);
				if (i < 4)
					arroftext[i].setPosition(50, 150 + 35 * (i - 2));
				else
					arroftext[i].setPosition(50, 350 + 50 * (i - 4));
			}

			for (int i = 0; i < 7; i++)
				window.draw(arroftext[i]);


		}

		else if (level_cnt == 5)
		{
			window.clear();
			window.draw(blanks);
			window.draw(backbuttons);
			 
			if (Mouse::isButtonPressed(Mouse::Left) && start_index.x >= 20 && start_index.x <= 62 && start_index.y >= 19 && start_index.y <= 63)
				level_cnt = 0;

				window.draw(easys);
				window.draw(hards);
				window.draw(okays);
				window.draw(diffarrows);

			if (start_index.x > 200 && start_index.x < 403 && start_index.y > 330 && start_index.y < 398) {
				//easy........
				diff = 1000;
				diffarrows.setPosition(easys.getPosition().x + 40, easys.getPosition().y + 80);

			}
			else if (start_index.x > 500 && start_index.x < 703 && start_index.y > 330 && start_index.y < 398) {
				//okay.........
				diff = 750;
				diffarrows.setPosition(okays.getPosition().x + 40, okays.getPosition().y + 80);

			}
			else if (start_index.x > 800 && start_index.x < 1003 && start_index.y > 330 && start_index.y < 398) {
				//hard.............
				diff = 350;
				diffarrows.setPosition(hards.getPosition().x + 40, hards.getPosition().y + 80);

		}

		}
		window.display();
	}
	return 0;
}


void Rand_Gen_Of_pipes(int arr[])
{
	srand(time(0));
	for (int i = 0; i < PIPES; i++) {
		int random = rand() % 300 + 85;


		arr[i] = random;
	}
}

void initialization_of_pipes(Sprite arrup[], Sprite arrdown[], int pos_arr[], Texture& pipe,int diff)
{
	for (int i = 0; i < PIPES; i++)
	{
		arrup[i].setTexture(pipe);
		arrup[i].setScale(2, -2);
		arrup[i].setPosition(900 + (i * diff), pos_arr[i]);

		arrdown[i].setTexture(pipe);
		arrdown[i].setScale(2, 2);
		arrdown[i].setPosition(900 + (i * diff), pos_arr[i] + 200);

	}
}

void set_shield_arr(shields arrofshields[], Texture& shield, Sprite arrup[], Sprite arrdown[],int & shieldcntr)
{
	
	for (int i = 0; i < 5; i++)
	{
		arrofshields[i].shields.setTexture(shield);
		arrofshields[i].shields.setPosition(arrdown[(2*i+1)*5].getPosition().x+50, arrdown[(2 * i + 1) * 5].getPosition().y - 150);
		arrofshields[i].shields.setScale(0.15, 0.15);
		arrofshields[i].touched = 0;
	}
	shieldcntr = 5;

}

void Initialize_background(RectangleShape arrback[], RectangleShape arrbase[], Texture& levelback, Texture& levelbase)
{
	for (int i = 0; i < PIPES; i++)
	{
		arrback[i].setTexture(&levelback);
		arrback[i].setSize(Vector2f(288, 512));
		arrback[i].setPosition(i * 288, 0);
		arrback[i].setScale(1, 1.401);

		arrbase[i].setTexture(&levelbase);
		arrbase[i].setSize(Vector2f(1200, 600));
		arrbase[i].setPosition(i * 288, 570);
	}
}

void check_pipe_collision(bool& collide, Sprite player1s, Sprite arrup[], Sprite arrdown[])
{
	for (int i = 0; i < PIPES; i++) {
		if (player1s.getGlobalBounds().intersects(arrup[i].getGlobalBounds()) || player1s.getGlobalBounds().intersects(arrdown[i].getGlobalBounds())) {
			collide = 1;
		}
	}

}

void check_base_collision(bool& collide, Sprite player1s, RectangleShape arrofbase[])
{
	for (int i = 0; i < PIPES; i++) {

		if (player1s.getGlobalBounds().intersects(arrofbase[i].getGlobalBounds()) && !collide)
		{
			collide = 1;
		}
	}
}
void collide_animation(Sprite& player1s, players arrofplayers[], RectangleShape arrofbase[], double& velocityy, bool touchedground)
{
	for (int i = 0; i <PIPES; i++)
	{
		player1s.setScale(2, -2);
		arrofplayers[0].players.setScale(2, -2);
		arrofplayers[1].players.setScale(0.17, -0.17);
		arrofplayers[2].players.setScale(0.12, -0.12);
		arrofplayers[3].players.setScale(0.09, -0.09);
		arrofplayers[4].players.setScale(0.13, -0.13); 
		arrofplayers[5].players.setScale(0.08, -0.08);



		if (player1s.getGlobalBounds().intersects(arrofbase[i].getGlobalBounds())) {
			velocityy = 0;
			touchedground = 1;
		}
		else if (!touchedground) {
			velocityy = 1;
		}
	}
	player1s.move(0, velocityy);
	for (int i = 0; i < 6; i++)
	{
		arrofplayers[i].players.move(0, velocityy);
	}
}
