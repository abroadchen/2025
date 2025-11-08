cmake_minimum_required(VERSION 3.29)
project(codeforces)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include_directories(src)

add_executable(codeforces
    src/C.cpp
        "src/2A Winner.cpp"
        "src/2B Theleastroundway.cpp"
        src/Commentatorproblem2C.cpp
        "src/3A Shortestpathoftheking.cpp"
        "src/3B Lorry.cpp"
        "src/3C Tic-tac-toe.cpp"
        src/LeastCostBracketSequence3D.cpp
        "src/4A Watermelon.cpp"
        "src/4B BeforeanExam.cpp"
        src/Registrationsystem4C.cpp
        src/MysteriousPresent4D.cpp
        src/ChatServer'sOutgoingTraffic5A.cpp
        src/CenterAlignment5B.cpp
        src/LongestRegularBracketSequence5C.cpp
        src/FollowTrafficRules5D.cpp
        "src/5E BindianSignalizing.cpp"
        "src/6A Triangle.cpp"
        src/President'sOffice6B.cpp
        "src/6C Alice,BobandChocolate.cpp"
        "src/6D LizardsandBasements.cpp"
        src/Exposition6E.cpp
        "src/7A KalevitchandChess.cpp"
        src/MemoryManager7B.cpp
        "src/7C Line.cpp"
        src/PalindromeDegree7D.cpp
        src/DefiningMacros7E.cpp
        "src/8A TrainandPeter.cpp"
        src/ObsessionwithRobots8B.cpp
        "src/8C LookingforOrder.cpp"
        "src/8D TwoFriends.cpp"
        "src/8E Beads.cpp"
        src/DieRoll9A.cpp
        "src/9B RunningStudent.cpp"
        src/Hexadecimal'sNumbers9C.cpp
        "src/9D Howmanytrees.cpp"
        "src/9E InterestingGraphandApples.cpp"
        src/PowerConsumptionCalculation10A.cpp
        src/CinemaCashier10B.cpp
        src/DigitalRoot10C.cpp
        "src/10D LCIS.cpp"
        src/Greedychange10E.cpp
        src/IncreasingSequence11A.cpp
        "src/11B JumpingJack.cpp"
        src/HowManySquares11C.cpp
        "src/11D ASimpleTask.cpp"
        src/Forward,march11E.cpp
        "src/12A SuperAgent.cpp"
        src/CorrectSolution12B.cpp
        src/Fruits12C.cpp
        "src/12D Ball.cpp"
        "src/12E Startoftheseason.cpp"
        src/Numbers13A.cpp
        "src/13B LetterA.cpp"
        "src/13C Sequence.cpp"
        "src/13D Triangles.cpp"
        "src/13E Holes.cpp"
        "src/14A Letter.cpp"
        "src/14B YoungPhotographer.cpp"
        src/FourSegments14C.cpp
        "src/14D TwoPaths.cpp"
        src/Camels14E.cpp
        src/CottageVillage15A.cpp
        "src/15B Laser.cpp"
        src/IndustrialNim15C.cpp
        "src/15D Map.cpp"
        "src/15E Triangles.cpp"
        src/Flag16A.cpp
        src/BurglarandMatches16B.cpp
        src/Monitor16C.cpp
        "src/16D Logging.cpp"
        src/Fish16E.cpp
        src/Noldbachproblem17A.cpp
        "src/17B Hierarchy.cpp"
        "src/17C Balance.cpp"
        src/Notepad17D.cpp
        src/Palisection17E.cpp
        "src/18A Triangle.cpp"
        src/Platforms18B.cpp
        "src/18C Stripe.cpp"
        "src/18D SellerBob.cpp"
        src/Flag2,18E.cpp
        "src/19A WorldFootballCup.cpp"
        src/CheckoutAssistant19B.cpp
        src/DeletionofRepeats19C.cpp
        src/Points19D.cpp
        src/test.cpp
        src/Fairy19E.cpp
        "src/20A BerOSfilesystem.cpp"
        src/Equation20B.cpp
        src/Dijkstra20C.cpp
        "src/21A JabberID.cpp"
        src/Intersection21B.cpp
        "src/21C Stripe2.cpp"
        "src/21D TravelingGraph.cpp"
        "src/22A SecondOrderStatistics.cpp"
        "src/22B BargainingTable.cpp"
        "src/22C SystemAdministrator.cpp"
        "src/22D Segments.cpp"
        "src/22E Scheme.cpp"
        "src/23A You'reGivenaString....cpp"
        src/Party23B.cpp
        src/OrangesandApples23C.cpp
        "src/23D Tetragon.cpp"
        "src/23E Tree.cpp"
        src/Ringroad24A.cpp
        src/F1Champions24B.cpp
        "src/24C Sequenceofpoints.cpp"
        src/Brokenrobot24D.cpp
        "src/24E Berlandcollider.cpp"
        "src/25A IQtest.cpp"
        src/Phonenumbers25B.cpp
        src/RoadsinBerland25C.cpp
        "src/25D RoadsnotonlyinBerland.cpp"
        "src/25E Test.cpp"
        "src/26A AlmostPrime.cpp"
        src/RegularBracketSequence26B.cpp
        src/Parquet26C.cpp
        "src/26D Tickets.cpp"
        src/Multithreading26E.cpp
        src/NextTest27A.cpp
        "src/27B Tournament.cpp"
        "src/27C UnorderedSubsequence.cpp"
        src/RingRoad2,27D.cpp
        src/NumberWithTheGivenAmountOfDivisors27E.cpp
        "src/28A BenderProblem.cpp"
        src/pSort28B.cpp
        "src/28C BathQueue.cpp"
        src/Don'tfear,DravDeiskind28D.cpp
        src/DravDesavestheworld28E.cpp
        "src/29A SpitProblem.cpp"
        "src/29B TrafficLights.cpp"
        "src/29C MailStamps.cpp"
        "src/29D AntontheTree.cpp"
        "src/29E Quarrel.cpp"
        "src/30A Accounting.cpp"
        src/CodeforcesWorldFinals30B.cpp
        "src/30C ShootingGallery.cpp"
        "src/30D King'sProblem.cpp"
        "src/30E TrickyandCleverPassword.cpp"
        "src/31A WormsEvolution.cpp"
        "src/31B SysadminBob.cpp"
        "src/31C Schedule.cpp"
        src/Chocolate31D.cpp
        "src/31E TVGame.cpp"
        src/Reconnaissance32A.cpp
        "src/32B Borze.cpp"
        src/Flea32C.cpp
        src/Constellation32D.cpp
        "src/32E Hide-and-Seek.cpp"
        "src/33A Whatisfordinner.cpp"
        "src/33B StringProblem.cpp"
        "src/33C WonderfulRandomizedSum.cpp"
        "src/33D Knights.cpp"
        "src/33E Helper.cpp"
        src/Reconnaissance2,34A.cpp
        "src/34B Sale.cpp"
        src/PageNumbers34C.cpp
        src/RoadMap34D.cpp
        src/Collisions34E.cpp
        "src/35A ShellGame.cpp"
        "src/35B Warehouse.cpp"
        src/FireAgain35C.cpp
        "src/35D Animals.cpp"
        src/Parade35E.cpp
        src/Extra-terrestrialIntelligence36A.cpp
        src/Fractal36B.cpp
        src/Bowls36C.cpp
        src/NewGamewithaChessPiece36D.cpp
        "src/36E TwoPaths.cpp"
        "src/37A Towers.cpp"
        src/ComputerGame37B.cpp
        src/OldBerlandLanguage37C.cpp
        "src/37D LessonTimetable.cpp"
        "src/37E TrialforChief.cpp"
        "src/38A Army.cpp"
        src/Chess38B.cpp
        "src/38C Blinds.cpp"
        "src/38D VasyatheArchitect.cpp"
        "src/38E Let'sGoRolling!.cpp"
        "src/38F SmartBoy.cpp"
        src/Queue38G.cpp
        "src/38H TheGreatMarathon.cpp"
        src/C*++Calculations39A.cpp
        src/CompanyIncomeGrowth39B.cpp
        "src/Moon Craters39C.cpp"
        src/CubicalPlanet39D.cpp
        "src/Pacifist frogs39F.cpp"
        "src/Inverse Function39G.cpp"
        "src/Multiplication Table39H.cpp"
        "src/39I Tram.cpp"
        "src/39J Spelling Check.cpp"
        "src/39K Testing.cpp"
        "src/Find Color40A.cpp"
        src/Repaintings40B.cpp
        "src/40C Berland Square.cpp"
        "src/40D Interesting Sequence.cpp"
        "src/Number Table40E.cpp"
        "src/41A Translation.cpp"
        "src/Martian Dollar41B.cpp"
        "src/Email address41C.cpp"
        src/Pawn41D.cpp
        src/3-cycles41E.cpp
        "src/Guilty --- to the kitchen!42A.cpp"
        "src/Game of chess unfinished42B.cpp"
        "src/42C Safe cracking.cpp"
        "src/42D Strange town.cpp"
        "src/42E Baldman and the military.cpp"
        src/Football43A.cpp
        "src/43B Letter.cpp"
        "src/43C Lucky Tickets.cpp"
        "src/43D Journey.cpp"
        src/Race43E.cpp
        "src/44A Indian Summer.cpp"
        src/Cola44B.cpp
        "src/44C Holidays.cpp"
        "src/44D Hyperdrive.cpp"
        "src/44E Anfisa the Monkey.cpp"
        "src/44F BerPaint.cpp"
        "src/44G Shooting Gallery.cpp"
        "src/Phone Number44H.cpp"
        "src/44I Toys.cpp"
        "src/44J Triminoes.cpp"
        "src/Codecraft III45A.cpp"
        "src/45B School.cpp"
        "src/Dancing Lessons45C.cpp"
        "src/Event Dates45D.cpp"
        src/Director45E.cpp
        "src/Goats and Wolves45F.cpp"
        "src/Prime Problem45G.cpp"
        "src/Road Problem45H.cpp"
        "src/45I TCMCF+++.cpp"
        "src/Planting Trees45J.cpp"
        "src/46A Ball Game.cpp"
        "src/46B T-shirts from Sponsor.cpp"
        "src/46C Hamsters and Tigers.cpp"
        "src/Parking Lot46D.cpp"
        src/Comb46E.cpp
        "src/Hercule Poirot Problem46F.cpp"
        "src/Emperor's Problem46G.cpp"
        "src/47A Triangular numbers.cpp"
        src/Coins47B.cpp
        src/Crossword47C.cpp
        "src/47D Safe.cpp"
        src/Cannon47E.cpp
        "src/48A Rock-paper-scissors.cpp"
        "src/48B Land Lot.cpp"
        "src/48C The Race.cpp"
        src/Permutations48D.cpp
        "src/Ivan the Fool VS Gorynych the Dragon48E.cpp"
        "src/48F Snow sellers.cpp"
        "src/Galaxy Union48G.cpp"
        "src/48H Black and White.cpp"
        "src/49A Sleuth.cpp"
        "src/49B Sum.cpp"
        src/Disposition49C.cpp
        src/Game49D.cpp
        "src/Common ancestor49E.cpp"
        "src/Domino piling50A.cpp"
        "src/Choosing Symbol Pairs50B.cpp"
        "src/50C Happy Farm 5.cpp"
        "src/50D Bombing.cpp"
        "src/50E Square Equation Roots.cpp"
        "src/Cheaterius's Problem51A.cpp"
        "src/51B bHTML Tables Analisys.cpp"
        "src/51C Three Base Stations.cpp"
        "src/Geometrical problem51D.cpp"
        src/Pentagon51E.cpp
        src/Caterpillar51F.cpp
        "src/52A 123-sequence.cpp"
        "src/Right Triangles52B.cpp"
        "src/Circular RMQ52C.cpp"
        "src/53A Autocomplete.cpp"
        "src/53B Blog Photo.cpp"
        "src/53C Little Frog.cpp"
        "src/Physical Education53D.cpp"
        "src/Dead Ends53E.cpp"
        src/Presents54A.cpp
        "src/Cutting Jigsaw Puzzle54B.cpp"
        "src/First Digit Law54C.cpp"
        "src/54D Writing a Song.cpp"
        "src/54E Vacuum Сleaner.cpp"
        "src/Flea travel55A.cpp"
        "src/55B Smallest number.cpp"
        "src/Pie or die55C.cpp"
        "src/55D Beautiful numbers.cpp"
        "src/55E Very simple problem.cpp"
        "src/56A Bar.cpp"
        "src/56B Spoilt Permutation.cpp"
        "src/Corporation Mail56C.cpp"
        "src/Changing a String56D.cpp"
        "src/Domino Principle56E.cpp"
        "src/Square Earth?57A.cpp"
        "src/Martian Architecture57B.cpp"
        "src/57C Array.cpp"
        "src/57D Journey.cpp"
        src/Chess57E.cpp
        "src/Chat room58A.cpp"
        src/Coins58B.cpp
        "src/58C Trees.cpp"
        "src/58D Calendar.cpp"
        src/Expression58E.cpp
        "src/59A Word.cpp"
        "src/Fortune Telling59B.cpp"
        "src/59C Title.cpp"
        "src/59D Team Arrangemen.cpp"
        "src/59E Shortest Path.cpp"
        "src/Where Are My Flakes?60A.cpp"
        "src/60B Serial Time!.cpp"
        "src/Mushroom Strife60C.cpp"
        "src/60D Savior.cpp"
        "src/Mushroom Gnomes60E.cpp"
        "src/61A Ultra-Fast Mathematician.cpp"
        "src/61B Hard Work.cpp"
        "src/Capture Valerian61C.cpp"
        "src/Eternal Victory61D.cpp"
        "src/Enemy is weak61E.cpp"
        "src/62A A Student's Dream.cpp"
        "src/62B Tyndex.Brome.cpp"
        "src/62C Inquisition.cpp"
        "src/62D Wormhouse.cpp"
        "src/62E World Evil.cpp"
        "src/63A Sinking Ship.cpp"
        "src/63B Settlers' Training.cpp"
        "src/Bulls and Cows63C.cpp"
        "src/Dividing Island63D.cpp"
        "src/63E Sweets Game.cpp"
        src/Factorial64A.tcl
        src/Expression64B.tcl
        "src/64C Table.tcl"
        src/Presents64D.tcl
        "src/Prime Segment64E.tcl"
        src/Domain64F.tcl
        "src/Path Canonization64G.tcl"
        "src/64H Table Bowling.tcl"
        "src/64I Sort the Table.tcl"
        "src/65A Harry Potter and Three Spells.cpp"
        "src/65B Harry Potter and the History of Magic.cpp"
        "src/65C Harry Potter and the Golden Snitch.cpp"
        "src/65D Harry Potter and the Sorting Hat.cpp"
        "src/65E Harry Potter and Moving Staircases.cpp"
        "src/Petya and Java66A.cpp"
        "src/Petya and Countryside66B.cpp"
        "src/Petya and File System66C.cpp"
        "src/Petya and His Friends66D.cpp"
        "src/Petya and Post66E.cpp"
        "src/Partial Teacher67A.cpp"
        "src/Restoration of the Permutation67B.cpp"
        "src/67C Sequence of Balls.cpp"
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
        "src/72I Goofy Numbers.io"
        "src/73A The Elder Trolls IV: Oblivon.cpp"
        "src/73B Need For Brake.cpp"
        "src/73C LionAge II.cpp"
        "src/73D FreeDiv.cpp"
        "src/73E Morrowindows.cpp"
        "src/73F Plane of Tanks.cpp"
        "src/74A Room Leader.cpp"
        "src/74B Train.cpp"
        "src/74C Chessboard Billiard.cpp"
        "src/74D Hanger.cpp"
        "src/74E Shift It!.cpp"
        "src/75A Life Without Zeros.cpp"
        "src/75B Facetook Priority Wall.cpp"
        "src/75C Modified GCD.cpp"
        "src/75D Big Maximum Sum.cpp"
        "src/75E Ship's Shortest Path.cpp"
        "src/76A Gift.cpp"
        "src/76B Mice.cpp"
        "src/76C Mutation.cpp"
        "src/76D Plus and xor.cpp"
        "src/76E Points.cpp"
        "src/76F Tourist.cpp"
        "src/77A Heroes.cpp"
        "src/77B Falling Anvils.cpp"
        "src/77C Beavermuncher-0xFF.cpp"
        "src/77D Domino Carpet.cpp"
        "src/77E Martian Food.cpp"
        "src/78A Haiku.cpp"
        "src/78B Easter Eggs.cpp"
        "src/78C Beaver Game.cpp"
        "src/78D Archer's Shot.cpp"
        "src/78E Evacuation.cpp"
        "src/79A Bus Game.cpp"
        "src/79B Colorful Field.cpp"
        "src/79C Beaver.cpp"
        "src/79D Password.cpp"
        "src/79E Security System.cpp"
        "src/80A Panoramix's Prediction.cpp"
        "src/80B Depression.cpp"
        "src/81A Plug-in.cpp"
        "src/81B Sequence Formatting.cpp"
        "src/81C Average Score.cpp"
        "src/81D Polycarp's Picture Gallery.cpp"
        "src/81E Pairs.cpp"
        "src/82A Double Cola.cpp"
        "src/82B Sets.cpp"
        "src/82C General Mobilization.cpp"
        "src/82D Two out of Three.cpp"
        "src/82E Corridor.cpp"
        "src/83A Magical Array.cpp"
        "src/83B Doctor.cpp"
        "src/83C Track.cpp"
        "src/83D Numbers.cpp"
        "src/83E Two Subsequences.cpp"
        "src/84A Toy Army.cpp"
        "src/84C Biathlon.cpp"
        "src/85A Domino.cpp"
        "src/85B Embassy Queue.cpp"
        "src/85C Petya and Tree.cpp"
        "src/85D Sum of Medians.cpp"
        "src/85E Guard Towers.cpp"
        "src/85E Guard Towers.cpp"
        "src/86A Reflection.cpp"
        "src/86B Tetris revisited.cpp"
        "src/86C Genetic engineering.cpp"
        "src/86D Powerful array.cpp"
        "src/86E Long sequence.cpp")

set_target_properties(codeforces PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
