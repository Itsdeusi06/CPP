#include "Critter.h"

/// <summary>
/// Constructor that initializes a Critter object with a name, hunger level, boredom level, and time interval for status updates.
/// It also displays a message indicating the Critter's birth.
/// </summary>
/// <param name="name">The name of the critter.</param>
/// <param name="hunger">Initial hunger level (0-10).</param>
/// <param name="boredom">Initial boredom level (0-10).</param>
/// <param name="timePass">Time interval before hunger and boredom increase.</param>
Critter::Critter(const string& name, int hunger, int boredom, int timePass) : m_Name(name), m_Hunger(hunger), m_Boredom(boredom), m_time(timePass) {
    cout << name << " with hunger level " << hunger << " and boredom level of " << boredom << " has been born!\n";
    cout << Critter_figure(0); 
}

/// <summary>
/// Destructor for Critter. If hunger and boredom reach 10, the critter "dies".
/// </summary>
Critter::~Critter() {
    if (m_Hunger >= 10 && m_Boredom >= 10) {
        cout << "Your critter named " << m_Name << ". Died.\n";
        cout << Critter_figure(4);
    }

}

/// <summary>
/// Displays the options menu where the user can interact with the critter.
/// </summary>
void Critter::OptionsMenu() {
    bool quit = false;
    int entrada = 0;

    while (!quit) {
        cout << "\nCurrently playing with: " << GetName() << "\n";
        Greet();

        cout << "\n\nChoose an option:";
        cout << "\n\t0 - Exit/Change Critter/Create/Delete critter\n\t1 - Change Name\n\t2 - Listen to your critter\n\t3 - Feed your critter";
        cout << "\n\t4 - Play with your critter\n\t5 - Tell a story\n\t6 - View stats\n\n";

        entrada = getValidatedInput(0, 6);

        switch (entrada) {
        case 0:
            quit = true;
            break;
        case 1:
            SetName();
            break;
        case 2:
            Talk();
            break;
        case 3:
            SetHunger();
            break;
        case 4:
            Play();
            break;
        case 5:
            Story();
            break;
        case 6:
            Peek(*this);
            break;
        default:
            cout << "Invalid option. Try again.\n";
        }
    }
}

/// <summary>
/// Retrieves the critter's hunger level.
/// </summary>
/// <returns>Returns an integer representing the hunger level.</returns>
int Critter::GetHunger() const {
    return m_Hunger;
}

/// <summary>
/// Feeds the critter by reducing hunger based on selected food.
/// </summary>
void Critter::SetHunger() {
    
    if (m_Hunger > 0)
    {     // arrays         0            1           2               3           4
        Food foods[] = { {"Meal", 5}, {"Fish", 5}, {"Candy", 1}, {"Bread", 2}, {"Sushi", 3} };
        int entrada;

        if (m_Hunger > 0) {
            cout << "Choose food:\n";
            for (int i = 0; i < 5; i++) {
                cout << i + 1 << " - " << foods[i].name << "\n";
            }
            entrada = getValidatedInput(1, 5);

            if (entrada >= 1 && entrada <= 5) {
                Food chosenFood = foods[entrada - 1];
                if (m_Hunger >= chosenFood.hungerValue) {
                    cout << "That was a nice " << chosenFood.name << ", thank you!\n";
                    m_Hunger -= chosenFood.hungerValue;
                    passTime(m_time); 
                }
                else {
                    cout << "No! I won't eat that!\n";
                    SetHunger();
                }
            }
            else {
                cout << "Invalid choice.\n";
            }
        }
    }
    else
    {
        cout << "I'm not hungry\n";
    }
    
}

/// <summary>
/// Retrieves the name of the critter.
/// </summary>
/// <returns>Returns the critter's name as a string.</returns>
string Critter::GetName() const {
    return m_Name;
}

/// <summary>
/// Allows the user to change the name of the critter.
/// </summary>
void Critter::SetName() {
    cout << "How do you want to name me?\n";
    cin.ignore();
    getline(cin, m_Name);
}

/// <summary>
/// Return the boredom of the critter
/// </summary>
/// <returns>Returns the name of the boredom</returns>
int Critter::GetBoredom() const {
    return m_Boredom;
}

/// <summary>
/// allows modify the boredom
/// </summary>
/// <param name="boredom">modify the boredom</param>
void Critter::SetBoredom(int boredom) {
    m_Boredom = boredom;
}

/// <summary>
/// the critter talk depending of the hunger and the boredom
/// </summary>
void Critter::Talk() {
    string mood;
    int figura;
    // He want to kill him self
    if (m_Hunger >= 9 || m_Boredom >= 9) {
        mood = "I'm thinking about giving up (KMS).\n"; 
        figura = 4;
    }
    // He starting to feel abandoned
    else if (m_Hunger >= 5 || m_Boredom >= 5) {
        mood = "I feel neglected.\n";
        figura = 2;
    }
    // He is a happy critter
    else {
        mood = "I'm happy!\n";
        figura = 1;
    }
    // show the face the mood saved and call teh pass time 
    cout << Critter_figure(figura);
    cout << mood << "\n";
    passTime(m_time);
}


/// <summary>
/// Plays with the critter to reduce boredom.
/// </summary>
void Critter::Play() {
    int boredom = m_Boredom - 1;// This make the boredom don't go up
    srand((int)time(0));
    int entrada;
    int numero = rand() % 20;
    bool guess = false;
    string acudit;

    cout << "What do you want to play?\n1 - Tell me a joke.\n2 - Play to guess the number (0 - 20).\n\n";
    entrada = getValidatedInput(1, 2);
    
    switch (entrada)
    {
    case 1:
        cin.ignore();
        cout << "Perfect!! Hope you are a good humorist.\n\n";
        getline(cin, acudit); 
        cout << "Puajajaja!! How are you this good OMG you should go profesional.\n\n";
        break;
    case 2:
        cout << "Ok I have a number. Between 1 AND 20.\n\n";
        while (!guess)
        {   
            cout << "Try to guess it.\n\n";
            
            /*HI THERE - Uncomment thsi to see the random number to test if it works :)
            cout << numero;
            */
            
            // Loop for the correct option
            entrada = getValidatedInput(0, 20);
            if (numero == entrada)
            {
                cout << "Fantastic, you guess it.\n\n";
                guess = true;
                break;
            }
            else
            {
                cout << "You miss. \n";
            }
        }
        break;
    default:
        cout << "Error has ocurred\n";
        break;
    }
    passTime(m_time);
    SetBoredom(boredom); // we call the function the last to subtract -1 to m_boredom
}

/// <summary>
/// tell a story to the critter 
/// </summary>
void Critter::Story() {
    int entrada;
    string song1;
    string song2;
    string song3;

    cout << "Which story song you want to hear\n1 - Violet's Tale\n2 - Hi Ren\n3 - Money Game\n\n";
    
    entrada = getValidatedInput(1, 3);

// Cançons d'artista de REN
    switch (entrada)
    {
    case 1:
    // Song 1: Violet’s Tales -- resum
        song1 = "Song 1: Violet's Tale\n"
            "The story begins in London, where Violet's life unfolds amidst violence and neglect. "
            "Born into a broken family, Violet experiences abuse and finds herself trapped in a cycle of silence and suffering. "
            "As she grows older, she falls into another toxic relationship with Stevie, repeating the pattern of violence she knew too well. "
            "The song expresses the brutality of her reality, her internal battle to stay silent, and the eventual breaking point where she reveals her struggle in the face of death.\n\n"
            "\"Violet, why you always so quiet? Knock-knock-knock... Fist connects and disconnects the bone. "
            "Violet, why you lying to me?\"\n"
            "\"Violet broke her silence and she cried, 'If I'm to die right here tonight, please let my baby stay alive.'\"\n\n"
            "In a tragic twist, Violet passes away, but not before giving birth to twins—Jenny and Screech, leaving behind a legacy of pain and survival.\n\n\n";
        cout << song1 << endl; 
        break;
    case 2:
    // Song 2: Hi Ren -- resum
        song2 = "Song 2: Hi Ren\n"
            "In this chapter, we shift to a more introspective battle within the protagonist, Ren. He faces a constant struggle with his inner demons, "
            "represented as an externalized voice that challenges his identity, music, and sanity. His inner voice taunts him, urging him to abandon his progress and return to a destructive path of self-doubt and insecurity. "
            "But Ren begins to resist, finding solace in the creative process and his music, which connects with people on a deeper level.\n\n"
            "\"Ren, you think that those doctors are really there to guide you? You've been through this a million times. Your civilian mind is so perfect at always being lied to.\"\n"
            "\"I am you, you are me, you are I, I am we. We are one, split in two that makes one, so you see. You got to kill you if you wanna kill me.\"\n\n"
            "The battle with his subconscious is intense, yet Ren learns that he must embrace both sides of himself in order to thrive and grow.\n\n\n";
        cout << song2;
        break;
    case 3:
    // Chapter 3: Money Game Pt. 2 -- resum
        song3 = "Song 3: Money Game\n"
            "The final chapter shifts focus to the broader societal context, revealing the corruption, greed, and manipulation that define the modern world. "
            "Ren comments on the manipulative structures of power, where individuals rise through lies, deceit, and a distorted reality. "
            "This chapter calls out the hypocrisy of society, especially focusing on economic manipulation, the media, and the political elite.\n\n"
            "\"Strange times we're living in, panic and hysteria. Poor man learn the rich man don't care for ya. Narcissist mindsets spread like malaria.\"\n"
            "\"Money is a game and the ladder we climb, turns a saint into a sinner with his finger in crime.\"\n\n"
            "The focus here is on the idea that we are all part of this game, whether we realize it or not. The storm of lies and corruption looms, and the song critiques not only the leaders but also the people who let these structures control their lives.\n\n\n";
        cout << song3;
        break;
    default:
        cout << "Error has ocurred\n";
        break;
    }
    passTime(m_time); 
}

/// <summary>
/// critter says hi and his name
/// </summary>
void Critter::Greet() {
    cout << "Hi I'm a critter named " << m_Name << ". And you are my pet sitter.\n";
}

/// <summary>
/// every time this function is called time is increased and if its 3 update the hunger and the boredeom 
/// </summary>
/// <param name="time">number to count the time passed while playing</param>
void Critter::passTime(int time) {
    m_time++;
    if (m_time == 3)
    {   
        m_Hunger++;
        m_Boredom++;
        m_time = 0;
        
        if (m_Hunger >= 10 && m_Boredom >= 10)
        {
            Critter::~Critter();
        }
        else
        {
            Talk();
        }
        
    }
}

/// <summary>
/// this saves faces of the critter in array
/// </summary>
/// <param name="figura">pass the number of the face he will have</param>
/// <returns>the face will show</returns>
string Critter::Critter_figure(int figura) {
    string cares[] = { 
    // cara normal Num 0
        R"(                                
         /\        /\
        (  o      o  )
         \   ----   /
          \________/
)",  
    // cara content Num 1
        R"(
         /\        /\
        (  ^      ^  )
         \   ----   /
          \________/
)", 
    // cara trist Num 2
        R"(

         /\        /\
        (  -      -  )
         \    ..    /
          \________/
)", 
    // cara mitg mort Num 3
        R"(
         /\        /\
        (  o      x  )
         \    ..    /
          \________/
)", 
    // cara mort Num 4
        R"(
         /\        /\
        (  x      x  )
         \   ----   /
          \________/
)" };
    return cares[figura];
}

/// <summary>
/// 100 names to set in the critters as teh default
/// </summary>
/// <param name="names">names is from the main to initialize in the mascota.cpp</param>
void getDefaultNames(string names[]) {
    // Using a list to directly populate the names array
    string tempNames[] = {
        "Jeff", "Elon", "Alice", "Bob", "Charlie", "David", "Eva", "Frank", "Grace", "Hannah",
        "Ivy", "Jack", "Kathy", "Liam", "Mason", "Nina", "Oscar", "Paul", "Quincy", "Rachel",
        "Sam", "Tina", "Ursula", "Victor", "Wendy", "Xander", "Yara", "Zane", "Abigail", "Ben",
        "Catherine", "Derek", "Ella", "Felix", "Gina", "Harry", "Isabel", "John", "Kim", "Lily",
        "Matthew", "Nancy", "Oliver", "Penny", "Quinn", "Ryan", "Sophia", "Tom", "Uma", "Vera",
        "Walter", "Xena", "Yvonne", "Zach", "Amy", "Brian", "Chloe", "Daniel", "Eva", "Faith",
        "George", "Helen", "Ian", "Jenna", "Kevin", "Lana", "Mark", "Nora", "Owen", "Piper",
        "Quinn", "Reed", "Sophie", "Travis", "Ursula", "Vince", "Willow", "Xander", "Yasmine", "Zoe",
        "Aria", "Blake", "Carla", "Dylan", "Elliot", "Fiona", "Gabe", "Hope", "Iris", "Jared",
        "Kara", "Leo", "Maya", "Nate", "Olivia", "Patrick", "Queenie", "Ryan", "Skylar", "Tristan"
    };

    // Copy the names from tempNames to the provided names array
    for (int i = 0; i < numNames; ++i) {
        names[i] = tempNames[i];
    }
}

/// <summary>
/// this verify the input 
/// </summary>
/// <param name="min">this is the min number that can be</param>
/// <param name="max">this is the max number that can be</param>
/// <returns>returns input so its correct</returns>
int getValidatedInput(int min, int max) {
    int input = 0;
    // Loop to validate the input is between min and max both are included
    while (!(cin >> input) || input < min || input > max) {
        // If the imput is not between
        cout << "Invalid input. Enter a number between " << min << " and " << max << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clears the input buffer
    }
    // Return the imput valided
    return input;
}

/// <summary>
/// Displays the critter's stats.
/// </summary>
/// <param name="aCritter">The Critter object to inspect.</param>
void Peek(const Critter& aCritter) {
    cout << "Peeking into Critter details:\n";
    cout << "Name: " << aCritter.m_Name << endl;
    cout << "Hunger: " << aCritter.m_Hunger << endl;
    cout << "Boredom: " << aCritter.m_Boredom << endl;
}

/// <summary>
/// Overload of the << (stream insertion) operator for the Critter class.
/// This allows a Critter object to be printed to an output stream (e.g., std::cout).
/// The output includes the Critter's name, hunger level, and boredom level.
/// </summary>
/// <param name="out">The output stream to which the Critter's details will be sent.</param>
/// <param name="critter">The Critter object whose details are being output.</param>
/// <returns>The modified output stream.</returns>
std::ostream& operator<<(std::ostream& out, const Critter& critter) {
    out << "Name: " << critter.m_Name << ", Hunger: " << critter.m_Hunger
        << ", Boredom: " << critter.m_Boredom;
    return out;
}
