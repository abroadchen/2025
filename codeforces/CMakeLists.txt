cmake_minimum_required(VERSION 3.29)
project(codeforces)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include_directories(src)

add_executable(codeforces
    src/C.cpp
        src/Winner2A.cpp
        src/Theleastroundway2B.cpp
        src/Commentatorproblem2C.cpp
        src/Shortestpathoftheking3A.cpp
        src/Lorry3B.cpp
        src/Tic-tac-toe3C.cpp
        src/LeastCostBracketSequence3D.cpp
        src/Watermelon4A.cpp
        src/BeforeanExam4B.cpp
        src/Registrationsystem4C.cpp
        src/MysteriousPresent4D.cpp
        src/ChatServer'sOutgoingTraffic5A.cpp
        src/CenterAlignment5B.cpp
        src/LongestRegularBracketSequence5C.cpp
        src/FollowTrafficRules5D.cpp
        src/BindianSignalizing5E.cpp
        src/Triangle6A.cpp
        src/President'sOffice6B.cpp
        src/Alice,BobandChocolate6C.cpp
        "src/LizardsandBasements6D .cpp"
        src/Exposition6E.cpp
        src/KalevitchandChess7A.cpp
        src/MemoryManager7B.cpp
        src/Line7C.cpp
        src/PalindromeDegree7D.cpp
        src/DefiningMacros7E.cpp
        src/TrainandPeter8A.cpp
        src/ObsessionwithRobots8B.cpp
        src/LookingforOrder8C.cpp
        src/TwoFriends8D.cpp
        src/Beads8E.cpp
        src/DieRoll9A.cpp
        src/RunningStudent9B.cpp
        src/Hexadecimal'sNumbers9C.cpp
        src/Howmanytrees9D.cpp
        src/InterestingGraphandApples9E.cpp
        src/PowerConsumptionCalculation10A.cpp
        src/CinemaCashier10B.cpp
        src/DigitalRoot10C.cpp
        src/LCIS10D.cpp
        src/Greedychange10E.cpp
        src/IncreasingSequence11A.cpp
        src/JumpingJack11B.cpp
        src/HowManySquares11C.cpp
        src/ASimpleTask11D.cpp
        src/Forward,march11E.cpp
        src/SuperAgent12A.cpp
        src/CorrectSolution12B.cpp
        src/Fruits12C.cpp
        src/Ball12D.cpp
        src/Startoftheseason12E.cpp
        src/Numbers13A.cpp
        src/LetterA13B.cpp
        src/Sequence13C.cpp
        src/Triangles13D.cpp
        src/Holes13E.cpp
        src/Letter14A.cpp
        src/YoungPhotographer14B.cpp
        src/FourSegments14C.cpp
        src/TwoPaths14D.cpp
        src/Camels14E.cpp
        src/CottageVillage15A.cpp
        src/Laser15B.cpp
        src/IndustrialNim15C.cpp
        src/Map15D.cpp
        src/Triangles15E.cpp
        src/Flag16A.cpp
        src/BurglarandMatches16B.cpp
        src/Monitor16C.cpp
        src/Logging16D.cpp
        src/Fish16E.cpp
        src/Noldbachproblem17A.cpp
        src/Hierarchy17B.cpp
        src/Balance17C.cpp
        src/Notepad17D.cpp
        src/Palisection17E.cpp
        src/Triangle18A.cpp
        src/Platforms18B.cpp
        src/Stripe18C.cpp
        src/SellerBob18D.cpp
        src/Flag2,18E.cpp
        src/WorldFootballCup19A.cpp
        src/CheckoutAssistant19B.cpp
        src/DeletionofRepeats19C.cpp
        src/Points19D.cpp
        src/test.cpp
        src/Fairy19E.cpp
        src/BerOSfilesystem20A.cpp
        src/Equation20B.cpp
        src/Dijkstra20C.cpp
        src/JabberID21A.cpp
        src/Intersection21B.cpp
        src/Stripe2_21C.cpp
        src/TravelingGraph21D.cpp
        src/SecondOrderStatistics22A.cpp
        src/BargainingTable22B.cpp
        src/SystemAdministrator22C.cpp
        src/Segments22D.cpp
        src/Scheme22E.cpp
        src/You'reGivenaString...23A.cpp
        src/Party23B.cpp
        src/OrangesandApples23C.cpp
        src/Tetragon23D.cpp
        src/Tree23E.cpp
        src/Ringroad24A.cpp
        src/F1Champions24B.cpp
        src/Sequenceofpoints24C.cpp
        src/Brokenrobot24D.cpp
        src/Berlandcollider24E.cpp
        src/IQtest25A.cpp
        src/Phonenumbers25B.cpp
        src/RoadsinBerland25C.cpp
        src/RoadsnotonlyinBerland25D.cpp
        src/Test25E.cpp
        src/AlmostPrime26A.cpp
        src/RegularBracketSequence26B.cpp
        src/Parquet26C.cpp
        src/Tickets26D.cpp
        src/Multithreading26E.cpp
        src/NextTest27A.cpp
        src/Tournament27B.cpp
        src/UnorderedSubsequence27C.cpp
        src/RingRoad2,27D.cpp
        src/NumberWithTheGivenAmountOfDivisors27E.cpp
        src/BenderProblem28A.cpp
        src/pSort28B.cpp
        src/BathQueue28C.cpp
        src/Don'tfear,DravDeiskind28D.cpp
        src/DravDesavestheworld28E.cpp
        src/SpitProblem29A.cpp
        src/TrafficLights29B.cpp
        src/MailStamps29C.cpp
        src/AntontheTree29D.cpp
        src/Quarrel29E.cpp
        src/Accounting30A.cpp
        src/CodeforcesWorldFinals30B.cpp
        src/ShootingGallery30C.cpp
        src/King'sProblem30D.cpp
        src/TrickyandCleverPassword30E.cpp
        src/WormsEvolution31A.cpp
        src/SysadminBob31B.cpp
        src/Schedule31C.cpp
        src/Chocolate31D.cpp
        src/TVGame31E.cpp
        src/Reconnaissance32A.cpp
        src/Borze32B.cpp
        src/Flea32C.cpp
        src/Constellation32D.cpp
        src/Hide-and-Seek32E.cpp
        src/Whatisfordinner33A.cpp
        src/StringProblem33B.cpp
        src/WonderfulRandomizedSum33C.cpp
        src/Knights33D.cpp
        src/Helper33E.cpp
        src/Reconnaissance2,34A.cpp
        src/Sale34B.cpp
        src/PageNumbers34C.cpp
        src/RoadMap34D.cpp
        src/Collisions34E.cpp
        src/ShellGame35A.cpp
        src/Warehouse35B.cpp
        src/FireAgain35C.cpp
        src/Animals35D.cpp
        src/Parade35E.cpp
        src/Extra-terrestrialIntelligence36A.cpp
        src/Fractal36B.cpp
        src/Bowls36C.cpp
        src/NewGamewithaChessPiece36D.cpp
        src/TwoPaths36E.cpp
        src/Towers37A.cpp
        src/ComputerGame37B.cpp
        src/OldBerlandLanguage37C.cpp
        src/LessonTimetable37D.cpp
        src/TrialforChief37E.cpp
        src/Army38A.cpp
        src/Chess38B.cpp
        src/Blinds38C.cpp
        src/VasyatheArchitect38D.cpp
        src/Let'sGoRolling!38E.cpp
        src/SmartBoy38F.cpp
        src/Queue38G.cpp
        src/TheGreatMarathon38H.cpp
        src/C*++Calculations39A.cpp
        src/CompanyIncomeGrowth39B.cpp
        "src/Moon Craters39C.cpp"
        src/CubicalPlanet39D.cpp
        "src/What Has Dirichlet Got to Do with That?39E.cpp"
        "src/Pacifist frogs39F.cpp"
        "src/Inverse Function39G.cpp"
        "src/Multiplication Table39H.cpp"
        src/Tram39I.cpp
        "src/Spelling Check39J.cpp"
        src/Testing39K.cpp
        "src/Find Color40A.cpp"
        src/Repaintings40B.cpp
        "src/Berland Square40C.cpp"
        "src/Interesting Sequence40D.cpp"
        "src/Number Table40E.cpp"
        src/Translation41A.cpp
        "src/Martian Dollar41B.cpp"
        "src/Email address41C.cpp"
        src/Pawn41D.cpp
        src/3-cycles41E.cpp
        "src/Guilty --- to the kitchen!42A.cpp"
        "src/Game of chess unfinished42B.cpp"
        "src/Safe cracking42C.cpp"
        "src/Strange town42D.cpp"
        "src/Baldman and the military42E.cpp"
        src/Football43A.cpp
        src/Letter43B.cpp
        "src/Lucky Tickets43C.cpp"
        src/Journey43D.cpp
        src/Race43E.cpp
        "src/Indian Summer44A.cpp"
        src/Cola44B.cpp
        src/Holidays44C.cpp
        src/Hyperdrive44D.cpp
        "src/Anfisa the Monkey44E.cpp"
        src/BerPaint44F.cpp
        "src/Shooting Gallery44G.cpp"
        "src/Phone Number44H.cpp"
        src/Toys44I.cpp
        src/Triminoes44J.cpp
        "src/Codecraft III45A.cpp"
        src/School45B.cpp
        "src/Dancing Lessons45C.cpp"
        "src/Event Dates45D.cpp"
        src/Director45E.cpp
        "src/Goats and Wolves45F.cpp"
        "src/Prime Problem45G.cpp"
        "src/Road Problem45H.cpp"
        src/TCMCF+++45I.cpp
        "src/Planting Trees45J.cpp"
        "src/Ball Game46A.cpp"
        "src/T-shirts from Sponsor46B.cpp"
        "src/Hamsters and Tigers46C.cpp"
        "src/Parking Lot46D.cpp"
        src/Comb46E.cpp
        "src/Hercule Poirot Problem46F.cpp"
        "src/Emperor's Problem46G.cpp"
        "src/Triangular numbers47A.cpp"
        src/Coins47B.cpp
        src/Crossword47C.cpp
        src/Safe47D.cpp
        src/Cannon47E.cpp
        src/Rock-paper-scissors48A.cpp
        "src/Land Lot48B.cpp"
        "src/The Race48C.cpp"
        src/Permutations48D.cpp
        "src/Ivan the Fool VS Gorynych the Dragon48E.cpp"
        "src/Snow sellers48F.cpp"
        "src/Galaxy Union48G.cpp"
        "src/Black and White48H.cpp"
        src/Sleuth49A.cpp
        src/Sum49B.cpp
        src/Disposition49C.cpp
        src/Game49D.cpp
        "src/Common ancestor49E.cpp"
        "src/Domino piling50A.cpp"
        "src/Choosing Symbol Pairs50B.cpp"
        "src/Happy Farm 5_50C.cpp"
        src/Bombing50D.cpp
        "src/Square Equation Roots50E.cpp"
        "src/Cheaterius's Problem51A.cpp"
        "src/bHTML Tables Analisys51B.cpp"
        "src/Three Base Stations51C.cpp"
        "src/Geometrical problem51D.cpp"
        src/Pentagon51E.cpp
        src/Caterpillar51F.cpp
        src/123-sequence52A.cpp
        "src/Right Triangles52B.cpp"
        "src/Circular RMQ52C.cpp"
        src/Autocomplete53A.cpp
        "src/Blog Photo53B.cpp"
        "src/Little Frog53C.cpp"
        "src/Physical Education53D.cpp"
        "src/Dead Ends53E.cpp"
        src/Presents54A.cpp
        "src/Cutting Jigsaw Puzzle54B.cpp"
        "src/First Digit Law54C.cpp"
        "src/Writing a Song54D.cpp"
        "src/Vacuum Сleaner54E.cpp"
        "src/Flea travel55A.cpp"
        "src/Smallest number55B.cpp"
        "src/Pie or die55C.cpp"
        "src/Beautiful numbers55D.cpp"
        "src/Very simple problem55E.cpp"
        src/Bar56A.cpp
        "src/Spoilt Permutation56B.cpp"
        "src/Corporation Mail56C.cpp"
        "src/Changing a String56D.cpp"
        "src/Domino Principle56E.cpp"
        "src/Square Earth?57A.cpp"
        "src/Martian Architecture57B.cpp"
        src/Array57C.cpp
        src/Journey57D.cpp
        src/Chess57E.cpp
        "src/Chat room58A.cpp"
        src/Coins58B.cpp
        src/Trees58C.cpp
        src/Calendar58D.cpp
        src/Expression58E.cpp
        src/Word59A.cpp
        "src/Fortune Telling59B.cpp"
        src/Title59C.cpp
        "src/Team Arrangemen59D.cpp"
        "src/Shortest Path59E.cpp"
        "src/Where Are My Flakes?60A.cpp"
        "src/Serial Time!60B.cpp"
        "src/Mushroom Strife60C.cpp"
        src/Savior60D.cpp
        "src/Mushroom Gnomes60E.cpp"
        "src/Ultra-Fast Mathematician61A.cpp"
        "src/Hard Work61B.cpp"
        "src/Capture Valerian61C.cpp"
        "src/Eternal Victory61D.cpp"
        "src/Enemy is weak61E.cpp"
        "src/A Student's Dream62A.cpp"
        src/Tyndex.Brome62B.cpp
        src/Inquisition62C.cpp
        src/Wormhouse62D.cpp
        "src/World Evil62E.cpp"
        "src/Sinking Ship63A.cpp"
        "src/Settlers' Training63B.cpp"
        "src/Bulls and Cows63C.cpp"
        "src/Dividing Island63D.cpp"
        "src/Sweets Game63E.cpp"
        src/Factorial64A.tcl
        src/Expression64B.tcl
        src/Table64C.tcl
        src/Presents64D.tcl
        "src/Prime Segment64E.tcl"
        src/Domain64F.tcl
        "src/Path Canonization64G.tcl"
        "src/Table Bowling64H.tcl"
        "src/Sort the Table64I.tcl"
        "src/Harry Potter and Three Spells65A.cpp"
        "src/Harry Potter and the History of Magic65B.cpp"
        "src/Harry Potter and the Golden Snitch65C.cpp"
        "src/Harry Potter and the Sorting Hat65D.cpp"
        "src/Harry Potter and Moving Staircases65E.cpp"
        "src/Petya and Java66A.cpp"
        "src/Petya and Countryside66B.cpp"
        "src/Petya and File System66C.cpp"
        "src/Petya and His Friends66D.cpp"
        "src/Petya and Post66E.cpp"
        "src/Partial Teacher67A.cpp"
        "src/Restoration of the Permutation67B.cpp"
        "src/Sequence of Balls67C.cpp"
        "src/Optical Experiment67D.cpp"
        "src/67E Save the City!.cpp"
        "src/68A Irrational problem.cpp"
        "src/68B Energy exchange.cpp"
        "src/68C Synchrophasotron.cpp"
        "src/68D Half-decay tree.cpp"
        "src/68E Contact.cpp"
        "src/69A Young Physicist.cpp"
        "src/69B Bets.cpp"
        "src/69C Game.cpp"
        "src/69D Dot.cpp"
        "src/69E Subsegments.cpp"
        "src/70A Cookies.cpp"
        "src/70B Text Messaging.cpp"
        "src/70C Lucky Tickets.cpp"
        "src/70D Professor's task.cpp"
        "src/70E Information Reform.cpp"
        "src/71A Way Too Long Words.cpp"
        "src/71B Progress Bar.cpp"
        "src/71C Round Table Knights.cpp"
        "src/71D Solitaire.cpp"
        "src/71E Nuclear Fusion.cpp"
        "src/72A Goshtasp, Vishtasp and Eidi.io"
        "src/72B INI-file.io"
        "src/72C Extraordinarily Nice Numbers.io"
        "src/72D Perse-script.io"
        "src/72E Ali goes shopping.io"
        "src/72F Oil.io"
        "src/72G Fibonacci army.io"
        "src/72H Reverse It!.io"
        "src/72I Goofy Numbers.io")

set_target_properties(codeforces PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
