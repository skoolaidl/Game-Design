#include "Strings.h"
#include <random>
#include <time.h>


Strings::Strings() {
    std::srand(time(0));

    strings.insert({ "Title", "Match Made in Hell" });
    strings.insert({ "CurrentLevel", "The Current Level is: " });
    strings.insert({ "MenuText", "Welcome to Match Made in Hell!\nPress s to go to the settings menu\nPress enter to start" });
    strings.insert({ "Settings", "Settings Menu\n" });
    strings.insert({ "SettingsText", "Press Backspace to return to the main menu\nPress the key you wish to change and then press\n the key you want" });
    strings.insert({ "CurrentKeys", "The current keybindings are : \n" });
    strings.insert({ "MoveRight", "Move Right: " });
    strings.insert({ "MoveLeft", "Move Left: " });
    strings.insert({ "Jump", "Jump: " });
    strings.insert({ "Shoot", "Shoot: " });
    strings.insert({ "NewLine", "\n" });
    strings.insert({ "ChangeLevel", "\nTo change the currently \nselected level, press 0-9, \nthe first level is 0" });

    responses.insert({"Rejections", { "Sorry babe, it's not me, it's you.",
        "This isn't gonna work out between us, but I'm sure you've got a great personality.",
        "I'd go out with you, but I'm gonna be sick that day.",
        "I'm sure you'll make some other guy, that's not me, really happy someday.",
        "Yikes, you looked a lot prettier from when I was at the start of the level.",
        "Yea, it's gonna be a no from me dawg.",
        "I'll call you if my plan A doesn't work out.",
        "If it's meant to be, it's meant to be... but just to be clear, it isn't.",
        "Sorry, you're just not my type. My type is attractive.",
        "Oh I see now. It must be girls like you that give Hell such a bad rap." }});
    responses.insert({ "DateYes", {"After much thought, I want to see what this relationship can evolve into!",
        "Ugh, you’re the perfect guy and I can’t see myself being with anyone else!",
        "Wow, you are my dream guy.I would love to go on a date with a hunk such as yourself.",
        "I didn’t think that I’d ever meet such a perfect guy, but here you are. I might be the luckiest demon in Hell.",
        "Wow, I can’t believe you massacred all of those pathetic demons just to impress me! You’ve definitely won my heart over.",
        "OMG, my daddy definitely wouldn't approve of you. You're perfect!",
        "Finally, I can stop searching! My Prince Charming has arrived.",
        "Finally, a man that can turn Hell into a romantic getaway. Where have you been all my life?",
        "OMG, you look like a guy who knows how to treat a lady. I've been waiting on my Romeo for all of eternity.",
        "Wow! I thought love at first sight only happened in fantasies. But I haven't been able to take my eyes off of you since you slaughtered that first demon."} });
    responses.insert({ "DateNo", {"Yikes, you just come off as a blow hard.You would definitely not be able to handle me.",
        "If you wanted to win me over, you’re gonna have to do a lot better than that. Pathetic.",
        "Geez,and I thought Hell was bad enough as is, but now I’ve got this weak excuse for a man hitting on me? No thanks.",
        "Wow, Satan was right, you don’t have any shot down here.You should probably just give up now.",
        "You really thought that was gonna be enough to impress me ? I should have just told you at the dating screen that I wasn’t interested.",
        "Are you kidding me? How about you try to be a semi-decent demon killer before you try to be a lady killer.",
        "Yikes, you're about 10 pixels too short for me. Maybe you should grow a little before trying to take on a woman like me.",
        "Hmmm... You don't seem genuine at all. So no thanks, cause you look like you'll just reject me or something if I liked you.",
        "Sorry, you're just not my type. My type is someone who wears even tighter leather and is a little more douchey than you.",
        "Gross, you don't have nearly enough abs or hairspray to date me. I can't believe you've wasted my time."} });

    preferences.insert({ "Kill", {"My stupid ex was a _ demon. Honestly, I hope he burns in Hell.",
        "My mom was a _ demon. She always babied me and never let me do anything!",
        "Those dumb and ugly _ demons have always annoyed me! Like why do they even exist?",
        "There was this group of _ demons in my highschool that constantly harassed me and totally ruined my chances of being popular!",
        "My obnoxious neighbor is part of a band called Satanic Vibes and the _ Demons,and I can never sleep because of their deafening heavy metal music.",
        "I can't believe Lexi the _ demon won Bachelorette in Hell. She was such a two-faced skank!",
        "Ugh, it seems like all _ demons are the same, they're all just hotheads.",
        "This one time, I was on a date and he would not stop checking out other girls. Never gonna trust a _ demon ever again.",
        "My _ demon stepsister always wants what she can't have. She is a minx who has repeatedly tried to steal my previous boyfriends.",
        "This one time, I was at Alexander the Amazing _ Demon's show and he made all my friends disappear. I've had no one to talk to ever since."} });
    preferences.insert({ "Ignore", {"My daddy was a _ demon.He always spoiled me and called me Daddy’s Little Princess.",
        "I miss my highschool clique of _ demons. We were some of the baddest mama jamas in all of Hell.",
        "My favorite musician is Chance the _ Demon Rapper. His singing pierces the soul I don't have.",
        "My big brother was a _ demon and he taught me everything I know. He even helped me possess my first porcelain doll.",
        "When I was younger, I always wanted to become like Draco the _ Demon. Legend has it, he single handedly caused the Chernobyl meltdown.",
        "I idolize my tough-skinned _ Grandpa. He fought in the legendary Demons and Angels War and obliterated an entire battalion of cherubs.",
        "My favorite character in my TV show just died. He was a _ demon with the perfect balance of cynicism and ruthlessness.",
        "When I was in college, my professor, Dr. _ Demon, inspired me to pursure a double major in Sadism and Witchcraft. Absolutely no regrets.",
        "My best friend was always there for me. If it wasn't for that amazing _ demon, Hell would be the absolute worst.",
        "If it wasn't for Yolanda the _ Torturer's inluence on my life on Earth, I might have ended up in Heaven.That would have been absolute torture!"} });

    tierList.push_back("Hopeless Mortal");
    tierList.push_back("Permanent Resident of the Friend Zone (aka Hell)");
    tierList.push_back("Average Douche");
    tierList.push_back("Satan’s Wingman");
    tierList.push_back("King of the Underworld");

    keys = {"A","B","C","D","E","F","G","H","I","J","K",
        "L","M","N","O",
        "P","Q","R","S",
        "T","U","V","W",
        "X","Y","Z","Num0",
        "Num1","Num2","Num3","Num4",
        "Num5","Num6","Num7","Num8",
        "Num9","Escape","LControl","LShift",
        "LAlt","LSystem","RControl","RShift",
        "RAlt","RSystem","Menu","LBracket",
        "RBracket","Semicolon","Comma","Period",
        "Quote","Slash","Backslash","Tilde",
        "Equal","Hyphen","Space","Enter",
        "Backspace","Tab","PageUp","PageDown",
        "End","Home","Insert","Delete",
        "Add","Subtract","Multiply","Divide",
        "Left","Right","Up","Down",
        "Numpad0","Numpad1","Numpad2","Numpad3",
        "Numpad4","Numpad5","Numpad6","Numpad7",
        "Numpad8","Numpad9","F1","F2",
        "F3","F4","F5","F6",
        "F7","F8","F9","F10",
        "F11","F12","F13","F14",
        "F15","Pause","KeyCount","Hyphen",
        "Backspace","Backslash","Semicolon","Enter" };
}

std::string Strings::getString(std::string key) {
    return strings[key];
}

std::string Strings::getResponse(std::string key) {
    return (responses[key])[(std::rand() % 10)];
}

std::string Strings::getTier(int rank) {
    return tierList[rank];
}

std::string Strings::getPreference(std::string key, int color) {
    std::string colText;
    switch (color) {
        case 0: colText = "red"; break;
        case 1: colText = "blue"; break;
        case 2: colText = "green"; break;
    }
    std::string pref;
    pref = preferences[key][(std::rand() % 10)];
    int index = pref.find("_");
    pref.insert(index, colText);
    return pref;

}

std::string Strings::getKey( int key ) {
    if (key == -1) {
        return "Unknown";
    }
    return keys[key];
}
