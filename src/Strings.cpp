#include "Strings.h"
#include <random>
#include <time.h>


Strings::Strings() {
    std::srand(time(0));

    strings.insert({ "Title", "Match Made in Hell" });
    strings.insert({ "CurrentLevel", "The Current Level is: " });
    strings.insert({ "Settings", "Settings Menu\n" });
    strings.insert({ "CurrentKeys", "The current keybindings are : \n" });
    strings.insert({ "MoveRight", "Move Right(RightArrow):" });
    strings.insert({ "MoveLeft", "Move Left(LeftArrow): " });
    strings.insert({ "Jump", "Jump(UpArrow): " });
    strings.insert({ "Shoot", "Shoot(Spacebar): " });
    strings.insert({ "NewLine", "\n" });
    strings.insert({ "LoadLevel", "\nTo load progress press L" });
    strings.insert({ "PressEnter", "Press enter to continue" });
    strings.insert({ "ChadRejected", "Pffft, I don't need you anyway! You've made the biggest \nmistake of your life, and you're gonna regret \nturning down THE Chad Chamberlain!" });
    strings.insert({ "WonLevel", "You successfully rejected the date\nYour score was: " });
    strings.insert({ "LostLevel", "You failed and got rejected by the girl\nYour score was: " });
    strings.insert({ "Tier", "Your tier based on the number of rejections\n                      Chad gave is:" });
    strings.insert({ "FinalScore", "Your final score is: "});
    strings.insert({ "FinalInstruct", "Press backspace to return to the menu, press escape to exit" });
    strings.insert({ "EndLevelInstruct", "Press backspace to return to the menu, press escape to exit\nPress R to replay the current level" });
    strings.insert({ "GoodLuck", "Good Luck Player!"});
    strings.insert({ "InstructionsTitle", "How to Play"});
    strings.insert({ "RightKey", "Right"});
    strings.insert({ "LeftKey", "Left"});
    strings.insert({ "JumpKey", "Up"});
    strings.insert({ "ShootKey", "Space"});
    strings.insert({ "ThankYou", "Thank you for playing our game,\n      we hoped you enjoyed it!"});
    strings.insert({ "Credits", "                        Created By:\nSeth Layton, Carter Greis, and Jordan Kula"});
    
    context = std::string("You are THE Chad Chamberlain, and you've been sent to Hell for your playboy lifestyle on Earth. ") + 
                        "Nonetheless, because of your lecherous way of living, a trip to Hell is not enough to deter you from pursuing nearby hotties. " +
                        "You must fight your way through a variety of demons, in an attempt to impress your dates and win them over.";
    instructions = std::string("Before every level, the date will describe her preference in demons to you, and you will have to pay attention to know which demons you should kill and which you should ignore. ") +
                        "If you are able to reach the date at the end of the level with a high enough score and within the time limit, you will win over that date! " +
                        "However, if you fail the level, you will be utterly embarrassed and rejected. " +
                        "Throughout the levels, you must avoid enemies, spikes, and pitfalls or suffer being sent back to the beginning of the level. " +
                        "To move left, press the " + getString("LeftKey") + " key. To move right, press the " + getString("RightKey") + " key. " +
                        "To jump, press the " + getString("JumpKey") + " key. To shoot, press the " + getString("ShootKey") + " key.";
    paragraphs.insert({ "Context", context});
    paragraphs.insert({ "Instructions", instructions});

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
        "Ugh, you're the perfect guy and I can't see myself being with anyone else!",
        "Wow, you are my dream guy. I would love to go on a date with a hunk such as yourself.",
        "I didn't think that I'd ever meet such a perfect guy, but here you are. I might be the luckiest demon in Hell.",
        "Wow, I can't believe you massacred all of those pathetic demons just to impress me! You've definitely won my heart over.",
        "OMG, my daddy definitely wouldn't approve of you. You're perfect!",
        "Finally, I can stop searching! My Prince Charming has arrived.",
        "Finally, a man that can turn Hell into a romantic getaway. Where have you been all my life?",
        "OMG, you look like a guy who knows how to treat a lady. I've been waiting on my Romeo for all of eternity.",
        "Wow! I thought love at first sight only happened in fantasies. But I haven't been able to take my eyes off of you since you slaughtered that first demon."} });
    responses.insert({ "DateNo", {"Yikes! You just come off as a blow hard. You would definitely not be able to handle me.",
        "If you wanted to win me over, you're gonna have to do a lot better than that. Pathetic!",
        "Geez, and I thought Hell was bad enough as is, but now I've got this weak excuse for a man hitting on me? No thanks.",
        "Wow, Satan was right, you don't have any shot down here. You should probably just give up now.",
        "You really thought that was gonna be enough to impress me? I should have just told you at the dating screen that I wasn't interested.",
        "Are you kidding me? How about you try to be a semi-decent demon killer before you try to be a lady killer.",
        "Yikes, you're about 10 pixels too short for me. Maybe you should grow a little before trying to take on a woman like me.",
        "Hmmm... You don't seem genuine at all. So no thanks, cause you look like you'll just reject me or something if I liked you.",
        "Sorry, you're just not my type. My type is someone who wears even tighter leather and is a little more douchey than you.",
        "Gross, you don't have nearly enough abs or hairspray to date me. I can't believe you've wasted my time."} });

    preferences.insert({ "Kill", {"My stupid ex was a *** demon. Honestly, I hope he burns in Hell.",
        "My mom was a *** demon. She always babied me and never let me do anything!",
        "Those dumb and ugly *** demons have always annoyed me! Like why do they even exist?",
        "There was this group of *** demons in my highschool that constantly harassed me and totally ruined my chances of being popular!",
        "My obnoxious neighbor is part of a band called Satanic Vibes and the *** Demons, and I can never sleep because of their deafening heavy metal music.",
        "I can't believe Lexi the *** demon won Bachelorette in Hell. She was such a two-faced skank!",
        "Ugh, it seems like all *** demons are the same, they're all just hotheads.",
        "This one time, I was on a date and he would not stop checking out other girls. Never gonna trust a *** demon ever again.",
        "My *** demon stepsister always wants what she can't have. She is a minx who has repeatedly tried to steal my previous boyfriends.",
        "This one time, I was at Alexander the Amazing *** Demon's show and he made all my friends disappear. I've had no one to talk to ever since."} });
    preferences.insert({ "Ignore", {"My daddy was a *** demon. He always spoiled me and called me Daddy's Little Princess.",
        "I miss my highschool clique of *** demons. We were some of the baddest mammajamas in all of Hell.",
        "My favorite musician is Chance the *** Demon Rapper. His singing pierces the soul I don't have.",
        "My big brother was a *** demon and he taught me everything I know. He even helped me possess my first porcelain doll.",
        "When I was younger, I always wanted to become like Draco the *** Demon. Legend has it, he single handedly caused the Chernobyl meltdown.",
        "I idolize my tough-skinned *** Grandpa. He fought in the legendary Demons and Angels War and obliterated an entire battalion of cherubs.",
        "My favorite character in my TV show just died. He was a *** demon with the perfect balance of cynicism and ruthlessness.",
        "When I was in college, my professor, Dr. *** Demon, inspired me to pursue a double major in Sadism and Witchcraft. Absolutely no regrets.",
        "My best friend was always there for me. If it wasn't for that amazing *** demon, Hell would be the absolute worst.",
        "If it wasn't for Yolanda the *** Torturer's influence on my life on Earth, I might have ended up in Heaven. That would have been absolute torture!"} });

    tierList.push_back("Hopeless Mortal");
    tierList.push_back("Permanent Resident of the Friend Zone");
    tierList.push_back("Average Douche");
    tierList.push_back("Satan's Wingman");
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

std::string Strings::getParagraph(std::string key)
{
    return insertNewLines(paragraphs[key], 46);
}

std::string Strings::insertNewLines(const std::string &in, const size_t every_n)
{
    std::string out;
    out.reserve(in.size() + in.size() / every_n);
    int spaceIndex = -1;
    for(std::string::size_type i = 0; i < in.size(); i++) {
        if (!(i % every_n) && i) {
            spaceIndex = in.find(' ', i)+1;
        }
        if (i == spaceIndex)
        {
            out.push_back('\n');
        }
        out.push_back(in[i]);
    }
    return out;
}

std::string Strings::getResponse(std::string key) {
    std::string response = (responses[key])[(std::rand() % responses[key].size())];
    return insertNewLines(response, 45);
}

std::string Strings::getTier(int rank) {
    if(rank < 0){
        rank = 0;
    }
    return insertNewLines(tierList[rank], 25);
}

std::string Strings::getPreference(std::string key, int color) {
    std::string colText;
    switch (color) {
        case 0: colText = "RED"; break;
        case 1: colText = "BLUE"; break;
        case 2: colText = "GREEN"; break;
        case 3: colText = "YELLOW"; break;
    }
    int randPref = std::rand() % preferences[key].size();
    //checks that the same preference string is not used in the same prelevel dialogue
    if(key == "Kill")
    {
        while(randPref == prevKillPref)
        {
            randPref = std::rand() % preferences[key].size();
        }
        prevKillPref = randPref;
    }
    else if(key == "Ignore")
    {
        while(randPref == prevIgnorePref)
        {
            randPref = std::rand() % preferences[key].size();
        }
        prevIgnorePref = randPref;
    }
    std::string pref;
    pref = preferences[key][randPref];
    int index = pref.find("***");
    pref.erase(index, 3);
    pref.insert(index, colText);
    return insertNewLines(pref, 40);

}

std::string Strings::getKey( int key ) {
    if (key == -1) {
        return "Unknown";
    }
    return keys[key];
}

void Strings::setString(std::string key, std::string value)
{
    strings[key] = value;
}

void Strings::updateInstructionsString()
{
    instructions = std::string("Before every level, the date will describe her preference in demons to you, and you will have to pay attention to know which demons you should kill and which you should ignore. ") +
                        "If you are able to reach the date at the end of the level with a high enough score and within the time limit, you will win over that date! " +
                        "However, if you fail the level, you will be utterly embarrassed and rejected. " +
                        "Throughout the levels, you must avoid enemies, spikes, and pitfalls or suffer being sent back to the beginning of the level. " +
                        "To move left, press the " + getString("LeftKey") + " key. To move right, press the " + getString("RightKey") + " key. " +
                        "To jump, press the " + getString("JumpKey") + " key. To shoot, press the " + getString("ShootKey") + " key.";
    paragraphs["Instructions"] = instructions;
}

