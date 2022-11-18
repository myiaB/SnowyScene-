/* A SFML Snowy scene created by Myia Boyle to fufill her OOP module assignment course work*/

#include <iostream>  
#include <SFML/Graphics.hpp> 
#include <random>
#include <vector>
#include <SFML/Audio.hpp>

using namespace std;

// define  window size
#define winWidth 610               
#define winHeight 400

//run program to make snow fall 
void createFlake(std::vector<sf::CircleShape>& arr);

// draw lines of snow and set position + colour + shape
void createFlake(std::vector<sf::CircleShape >& arr) {
    sf::CircleShape snowflake(float(rand()) / (float)(RAND_MAX / 3.0f) + 0.5f);
    snowflake.setPosition(float(rand() % winWidth), 0.0f);
    snowflake.setFillColor(sf::Color::White);

    arr.emplace_back(snowflake);
}

int main() {


    sf:: Music music;
    music.openFromFile("JINGLES.wav");
        music.play();


    int elapsed = 0;
    srand((unsigned int)time(0));
    std::vector<sf::CircleShape>snowflake;

    sf::Vector2f sledposition(30.0f, 13.0f);

    // create the window
    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Snowy Scene");

    // Texture set up of images
    sf::Texture tex_background, tex_snowman, tex_santaSled, tex_snowflakeSPR, tex_ChristmasText, tex_presents;
    tex_background.loadFromFile("SnowyScene_image.jpg");
    tex_snowman.loadFromFile("snowman.png");
    tex_santaSled.loadFromFile("santaSled.png");
    tex_snowflakeSPR.loadFromFile("UPCLOSEsnowflake-removebg-preview.png");
    tex_ChristmasText.loadFromFile("ChristmasText.png");
    tex_presents.loadFromFile("presents.png");

    // Sprite set up
    sf::Sprite spr_background, spr_snowman, spr_santaSled, spr_snowflakeSPR, spr_ChristmasText, spr_presents;

    spr_background.setTexture(tex_background);
    spr_snowman.setTexture(tex_snowman);
    spr_santaSled.setTexture(tex_santaSled);
    spr_snowflakeSPR.setTexture(tex_snowflakeSPR);
    spr_ChristmasText.setTexture(tex_ChristmasText);
    spr_presents.setTexture(tex_presents);



    //scale and position set up  of snowman 
    spr_snowman.scale(sf::Vector2f(0.35f, 0.35f));
    spr_snowman.setPosition(sf::Vector2f(275.0f, 210.0f));

    //set Text position
    spr_ChristmasText.scale(sf::Vector2f(0.35f, 0.35f));
    spr_ChristmasText.setPosition(sf::Vector2f(5.0f, 250.0f));

    //SANTA MOVE
    spr_santaSled.scale(sf::Vector2f(0.25f, 0.30f));
    spr_santaSled.setPosition(sf::Vector2f(10.0f, 10.0f));
    sf::Vector2f santaSpeed = sf::Vector2f(0.01f, 0.0f);


    // SPECIAL SNOW FLAKE FALL 
    spr_snowflakeSPR.scale(sf::Vector2f(0.05f, 0.06f));
    spr_snowflakeSPR.setPosition(500.0f, 0.0f);
    sf::Vector2f snowflakeSPRspeed = sf::Vector2f(0.0f, 0.01f);

    //make pressies fall 
    spr_presents.scale(sf::Vector2f(0.09f, 0.09f));
    spr_presents.setPosition(40.0f, 100.0f);
    sf::Vector2f presentsSpeed = sf::Vector2f(0.0f, 0.01);


    /*********************Windowtime+ drawing*******************************/
    sf::Clock clock;
    sf::Time elapsedTime;


    // run the program as long as the window is open
    while (window.isOpen()) {


        elapsed++;

        sf::Event event;
        while (window.pollEvent(event))
        {



            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }


        // clear the window with black color
        window.clear(sf::Color::Black);


        // drawing images 

        window.draw(spr_background);
        window.draw(spr_snowman);
        window.draw(spr_santaSled);
        window.draw(spr_snowflakeSPR);
        window.draw(spr_ChristmasText);
        window.draw(spr_presents);


        //calling method to draw flakes
        createFlake(snowflake);

        //accessing individual flakes and moving them 
        for (int i = 0; i < snowflake.size(); i++) {
            snowflake[i].move(0.0f, snowflake[i].getRadius() * 0.4f);
            window.draw(snowflake[i]);

            if (snowflake[i].getPosition().y >= winHeight) {

                snowflake.erase(snowflake.begin() + i);
            }
        }

        // end the current frame
        window.display();

        elapsedTime = clock.getElapsedTime();

        // if(spr_santaSled.getPosition.x  > 798){
        //     spr_santaSled.setPosition(30.0f, 13.0f);   
        //     spr_santaSled.move(santaSpeed);
        // }
        // while (spr_snowflakeSPR.position != (winHeight * -1)){
        // spr_snowflakeSPR.move(snowflakeSPRspeed);
        // }


        //moving sprites in window 
        spr_snowflakeSPR.move(snowflakeSPRspeed);
        spr_presents.move(presentsSpeed);

        //spr_santaSled.move(santaSpeed);

       //trying to get santa to loop back into frame.
        sf::Vector2f sledPosition = spr_santaSled.getPosition();
        if (sledPosition == sf::Vector2f(600.0f, 13.0f)) {
            spr_santaSled.setPosition(sf::Vector2f(30.0f, 13.0f));
            window.draw(spr_santaSled);
            spr_santaSled.move(santaSpeed);
        }
        else {
            spr_santaSled.move(santaSpeed);
        }

    }
    return 0;
}

