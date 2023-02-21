/*

Sudoku

Copyright © 21/02/2023 arinakostina-exe

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/


// The framerate management, which is between these lines-->     // { -------------------- }
// is from https://github.com/Kofybrek/Tetris/blob/Main/Source/Main.cpp
// Maybe there is a slight decrease in cpu consumption, but even without these lines of code the program works fine


#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <chrono>
#include <cstring>

#include "gridTemplate.cpp"

#define L 9
using namespace std;

bool firstMouseClick = false;

int main()

{   
    ///   PUT THE DIFFICULTY HERE (VALUE BETWEEN 0 - 81, THE BIGGER THE VALUE - THE MORE DIFFICULT)   ///

    int dif = 20;

    ///////////////////////////////////////////////////////////////////////////////////////////////

    int validMoves = dif;
    gridTemplate A(dif);

    string pics[] = {"Images/grid.jpg" , "Images/lines.png" , "Images/nums.png" , "Images/x.png", "Images/spongebob_gj.jpg"};
    

    //make the textures
    sf::Texture grid, lines, num, X, emoji;

    grid.loadFromFile(pics[0]);
    if (!grid.loadFromFile(pics[0]))
        return -1;
    lines.loadFromFile(pics[1]);
    if (!lines.loadFromFile(pics[1]))
        return -1;
    num.loadFromFile(pics[2]);
    if (!num.loadFromFile(pics[2]))
        return -1;
    X.loadFromFile(pics[3]);
    if (!X.loadFromFile(pics[3]))
        return -1;
    emoji.loadFromFile(pics[4]);
    if (!emoji.loadFromFile(pics[4]))
        return -1;

    //make the sprites
    sf::Sprite gridSprite, lineSprite1, lineSprite2, numSprite, Xsprite, emojiSprite;
    gridSprite.setTexture(grid);
    lineSprite1.setTexture(lines);
    lineSprite2.setTexture(lines);
    numSprite.setTexture(num);
    Xsprite.setTexture(X);
    emojiSprite.setTexture(emoji);


    //make the grid an image to get the size to create the window accordingly
    sf::Image Image;      
    Image.loadFromFile(pics[0]);
    float Width, Height;
    if (!Image.loadFromFile(pics[0]))
        return -1;

    Height = Image.getSize().y;
    Width  = Image.getSize().x;

    // create the window
    sf::RenderWindow window(sf::VideoMode(Width, Height), "Sudoku");    

    sf::RenderTexture renderTexture;
    renderTexture.clear();

    auto tp1 = chrono::system_clock::now();
    auto tp2 = chrono::system_clock::now();
	float fElapsedTime;
    sf::Event event;

// { --------------------------------------------
    // Used to make the game framerate-independent
	unsigned lag = 0;

    // Similar to lag, used to make the game framerate-independent
	std::chrono::time_point<std::chrono::steady_clock> previous_time;

	// Random device
	std::random_device random_device;

	// Random engine
	std::default_random_engine random_engine(random_device());

    // Get the current time and store it in the variable
	previous_time = std::chrono::steady_clock::now();

    unsigned FRAME_DURATION = 5;
//-------------------------------------------- }


    //main loop
    while (window.isOpen())
    {   

// { ---------------------------------------------
        //Get the difference in time between the current frame and the previous frame
		unsigned delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();

		//Add the difference to the lag
		lag += delta_time;

		//In other words, we're updating the current time for the next frame.
		previous_time += std::chrono::microseconds(delta_time);


        while (FRAME_DURATION <= lag)
		{
			//Subtract the right thing from the left thing
			lag -= FRAME_DURATION;
//---------------------------------------------- }


            // check all the windows events that were triggered since the last iteration of the loop
        
            while (window.pollEvent(event))
            {
                // "close requested" event: we close the window
                if (event.type == sf::Event::Closed)
                    window.close();

                // if space bar is pressed new game will be created
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)){

                    // Reset the valid moves with the start of the new game
                    validMoves = dif;

                    srand(time(0));
                    A.refillAll();

                }

                // check if a number was pressed
                if ((event.type == sf::Event::KeyPressed) && (event.key.code >= sf::Keyboard::Num1) &&  (event.key.code <= sf::Keyboard::Num9) && firstMouseClick){
                    int x = (int)(lineSprite1.getPosition().x)/67-2;
                    int y = (int)(lineSprite2.getPosition().y)/67-2;


                    // If the cell is empty we can check if the value pressed can be put in it
                    if(A.getCell(y,x) == 0){
                        A.putValue(y,x,(int)(event.key.code)-26);

                        // check if the value is -1
                        if(A.getCell(y, x) == -1)
                            tp1 = chrono::system_clock::now();
                        else
                            validMoves--;              
                    }
                }
            }

            bool b_pressing = sf::Mouse::isButtonPressed(sf::Mouse::Left);

            float mouseX, mouseY;
            //get the mouse position
            if(b_pressing){
                mouseX = (float)sf::Mouse::getPosition(window).x * window.getView().getSize().x / window.getSize().x;
                mouseY = (float)sf::Mouse::getPosition(window).y * window.getView().getSize().y / window.getSize().y;
            }      


            //draw the grid
            renderTexture.draw(gridSprite);
            window.draw(gridSprite);


            //draw the lines if player pressed in limits
            if(mouseX>67 && mouseX<670 && mouseY>134 && mouseY<737 ){
                firstMouseClick = true;

                lineSprite1.setPosition((int)(abs(mouseX))/67*67+67, 134);
                lineSprite1.setRotation(90);
                renderTexture.draw(lineSprite1);

                lineSprite2.setPosition(67, (int)(abs(mouseY))/67*67);
                renderTexture.draw(lineSprite2);

                window.draw(lineSprite1);
                window.draw(lineSprite2);       
            }

            //draw the already known numbers
            for(int k=0; k<L; k++){
                for(int i=0; i<L; i++){
                    if(A.getCell(k, i)!=0 && A.getCell(k, i)!=-1){
                        numSprite.setTextureRect(sf::IntRect((A.getCell(k, i)-1)*67, 0, 67, 67));
                        numSprite.setPosition((i+1)*67, (k+2)*67);
                        renderTexture.draw(numSprite);

                        window.draw(numSprite);
                    }
                    if(A.getCell(k, i) == -1){   // -1 represents that the number given is wrong, so picture x will appear for 0.3 sec
                        Xsprite.setPosition((i+1)*67, (k+2)*67);
                        window.draw(Xsprite);

                        // Measure the time that had passed since this cell was found to be -1, which we do by 
                        // subtracting tp1(which is when the cell became -1) from tp2(which is the time now)
                        tp2 = chrono::system_clock::now();
	                    chrono::duration<float> elapsedTime = tp2 - tp1;
	                    float fElapsedTime = elapsedTime.count();

                        // If the value that we found above (tp2 - tp1) is more than 0.3 sec then the picture x should dissapear, 
                        // so we put 0 in that cell
                        if(fElapsedTime>0.3f){
                            A.putRawValue(k, i, 0);
                        }  
                    }
                }
            }

            // Drawing the emoji when the game is finished
            if(validMoves == 0){
                renderTexture.draw(emojiSprite);
                window.draw(emojiSprite);
            }

            renderTexture.display();
            window.display();

        }   
    }      

    return 0;
}
