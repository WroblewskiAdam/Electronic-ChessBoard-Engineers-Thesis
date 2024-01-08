#pragma once
#include <Arduino.h>
#include <array>

#define s0 14
#define s1 12
#define s2 13
#define s3 27
#define sig1 35
#define sig2 34
#define sig3 39
#define sig4 36


class Detector
{
    public:
        Detector();
        void scanBoard();
        void printChar(const std::array<std::array<char, 8>, 8> &myArray);
        void printInt(const std::array<std::array<int, 8>, 8> &myArray);

        void clear_array(std::array<std::array<int, 8>, 8> &myArray);

    // private:
        void clearFigArray(std::array<std::array<char, 8>, 8> &myArray);
        void choosePin(int Pin);
        void mapToFigure();
        void getDropDown();
        void scan(bool reference);
        
        bool detect_board_change();

        void check_for_picked_fig();
        void check_for_placed_back();
        void check_for_move();
        void check_for_new_fig();
        
        int reading_num = 50;

        int change_row = -1;
        int change_col = -1;

        bool is_fig_picked = false;
        char picked_fig = 'X';
        int picked_row = -1;
        int picked_col = -1;

        int new_row = -1;
        int new_col = -1;

        int iter = 0;

        std::array<std::array<int, 8>, 8> referenceValues =   {{{0,0,0,0,0,0,0,0}, // potrzebne do obliczania dropdownu 
                                                                {0,0,0,0,0,0,0,0},
                                                                {0,0,0,0,0,0,0,0},
                                                                {0,0,0,0,0,0,0,0},
                                                                {0,0,0,0,0,0,0,0},
                                                                {0,0,0,0,0,0,0,0},
                                                                {0,0,0,0,0,0,0,0},
                                                                {0,0,0,0,0,0,0,0}}};

        std::array<std::array<int, 8>, 8> rawValues = {{{0,0,0,0,0,0,0,0},
                                                        {0,0,0,0,0,0,0,0},
                                                        {0,0,0,0,0,0,0,0},
                                                        {0,0,0,0,0,0,0,0},
                                                        {0,0,0,0,0,0,0,0},
                                                        {0,0,0,0,0,0,0,0},
                                                        {0,0,0,0,0,0,0,0},
                                                        {0,0,0,0,0,0,0,0}}};
        
        std::array<std::array<int, 8>, 8> dropDown =  {{{0,0,0,0,0,0,0,0},
                                                        {0,0,0,0,0,0,0,0},
                                                        {0,0,0,0,0,0,0,0},
                                                        {0,0,0,0,0,0,0,0},
                                                        {0,0,0,0,0,0,0,0},
                                                        {0,0,0,0,0,0,0,0},
                                                        {0,0,0,0,0,0,0,0},
                                                        {0,0,0,0,0,0,0,0}}};
        

        std::array<std::array<char, 8>, 8> figures =  {{{'0','0','0','0','0','0','0','0'},
                                                        {'0','0','0','0','0','0','0','0'},
                                                        {'0','0','0','0','0','0','0','0'},
                                                        {'0','0','0','0','0','0','0','0'},
                                                        {'0','0','0','0','0','0','0','0'},
                                                        {'0','0','0','0','0','0','0','0'},
                                                        {'0','0','0','0','0','0','0','0'},
                                                        {'0','0','0','0','0','0','0','0'}}};

        std::array<std::array<char, 8>, 8> prev_figures = {{{'0','0','0','0','0','0','0','0'},
                                                            {'0','0','0','0','0','0','0','0'},
                                                            {'0','0','0','0','0','0','0','0'},
                                                            {'0','0','0','0','0','0','0','0'},
                                                            {'0','0','0','0','0','0','0','0'},
                                                            {'0','0','0','0','0','0','0','0'},
                                                            {'0','0','0','0','0','0','0','0'},
                                                            {'0','0','0','0','0','0','0','0'}}};
                                                            
        std::array<std::array<char, 8>, 8> fig_before_change = {{{'0','0','0','0','0','0','0','0'},
                                                            {'0','0','0','0','0','0','0','0'},
                                                            {'0','0','0','0','0','0','0','0'},
                                                            {'0','0','0','0','0','0','0','0'},
                                                            {'0','0','0','0','0','0','0','0'},
                                                            {'0','0','0','0','0','0','0','0'},
                                                            {'0','0','0','0','0','0','0','0'},
                                                            {'0','0','0','0','0','0','0','0'}}};


        // tablica kalibracji wartosci dla kazdego czujnika
        const int calibration[12][8][8] = {
                    {{1323,1330,1370,1375,1379,1333,1350,1365}, //0
                    {1324,1387,1311,1378,1350,1296,1344,1327},
                    {1342,1353,1364,1364,1352,1258,1360,1348},
                    {1321,1336,1340,1351,1327,1405,1412,1397},
                    {1363,1409,1205,1325,1182,1317,1286,1322},
                    {1347,1395,1430,1250,1398,1278,1331,1256},
                    {1313,1318,1287,1290,1299,1313,1241,1291},
                    {1313,1244,1306,1331,1311,1344,1343,1280}}, 

                    {{730,733,730,779,740,710,858,800}, // 1
                    {700,684,847,723,751,714,793,716},
                    {691,830,742,717,790,755,704,710},
                    {690,745,748,693,740,722,807,814},
                    {695,704,710,728,657,693,719,705},
                    {707,706,711,615,711,678,676,706},
                    {717,663,659,699,730,696,682,669},
                    {687,686,683,674,663,693,664,638}},

                    {{538,538,537,573,540,536,623,590}, // 1,5 
                    {519,507,620,537,550,549,591,531},
                    {520,610,547,531,582,552,520,526},
                    {510,551,548,514,543,532,595,599},
                    {509,518,523,529,492,503,528,523},
                    {531,521,527,454,523,500,497,519},
                    {525,488,488,512,537,510,503,496},
                    {528,507,504,500,493,513,493,476}},

                    {{281,245,275,281,258,261,281,289}, //2,5
                    {253,249,297,265,269,277,306,309},
                    {263,286,303,305,288,274,256,263},
                    {268,300,320,356,279,271,318,281},
                    {251,274,244,263,251,255,261,261},
                    {253,247,247,261,253,251,243,239},
                    {251,236,254,259,251,256,261,234},
                    {277,256,254,242,245,266,221,259}},

                    {{109,107,110,116,111,105,126,117}, //4,5
                    {105,106,126,108,110,110,118,106},
                    {104,120,106,107,115,110,105,105},
                    {103,108,108,107,107,106,120,120},
                    {103,106,103,103,101,103,105,105},
                    {105,104,106,94,103,101,103,102},
                    {105,99,100,101,106,102,103,102},
                    {105,101,102,100,101,104,100,97}},

                    {{39,39,40,44,40,40,46,45}, //7
                    {38,39,46,40,41,39,44,40},
                    {40,46,38,40,44,40,40,38},
                    {38,39,40,40,40,40,45,45},
                    {38,38,39,40,36,38,39,39},
                    {39,39,38,36,38,37,37,39},
                    {39,36,36,37,40,38,38,41},
                    {39,37,39,38,39,38,39,37}},



                    {{-1264,-1254,-1215,-1217,-1209,-1240,-1260,-1230}, // -0
                    {-1246,-1183,-1304,-1200,-1256,-1295,-1253,-1248},
                    {-1230,-1258,-1228,-1215,-1246,-1326,-1212,-1232},
                    {-1244,-1257,-1253,-1236,-1264,-1181,-1195,-1204},
                    {-1171,-1120,-1337,-1227,-1333,-1222,-1261,-1215},
                    {-1204,-1138,-1117,-1195,-1151,-1255,-1203,-1292},
                    {-1231,-1185,-1227,-1240,-1226,-1226,-1149,-1225},
                    {-1235,-1271,-1225,-1186,-1208,-1200,-1172,-1220}},

                    {{-734,-718,-741,-775,-747,-723,-855,-799}, // -1
                    {-700,-686,-848,-728,-755,-745,-807,-719},
                    {-705,-831,-756,-721,-783,-759,-708,-716},
                    {-693,-748,-750,-686,-731,-722,-805,-803},
                    {-691,-698,-711,-729,-666,-685,-720,-716},
                    {-728,-704,-701,-612,-709,-679,-672,-705},
                    {-716,-659,-651,-696,-725,-693,-682,-662},
                    {-711,-684,-681,-672,-659,-694,-661,-638}},
                    
                    {{-511,-507,-511,-538,-512,-501,-589,-552}, // -1,5
                    {-491,-475,-590,-503,-526,-518,-552,-503},
                    {-492,-576,-523,-501,-547,-520,-497,-499},
                    {-485,-522,-517,-477,-512,-502,-556,-560},
                    {-483,-485,-491,-504,-464,-480,-502,-497},
                    {-503,-491,-493,-433,-493,-477,-469,-492},
                    {-499,-461,-464,-485,-504,-483,-474,-461},
                    {-496,-474,-482,-470,-462,-484,-462,-451}},
                    
                    {{-317,-312,-317,-333,-316,-311,-366,-345}, // -2,5
                    {-300,-296,-363,-313,-321,-317,-341,-307},
                    {-302,-352,-320,-312,-337,-322,-308,-308},
                    {-301,-319,-319,-299,-316,-310,-343,-346},
                    {-298,-300,-294,-308,-283,-295,-307,-304},
                    {-306,-302,-305,-269,-303,-294,-287,-302},
                    {-307,-286,-285,-295,-308,-295,-292,-283},
                    {-305,-291,-296,-290,-284,-298,-285,-280}},
                    
                    {{-104,-103,-103,-110,-103,-102,-118,-112}, // -4,5
                    {-101,-97,-118,-103,-106,-104,-113,-102},
                    {-99,-116,-106,-102,-111,-104,-100,-101},
                    {-100,-104,-104,-100,-104,-101,-113,-114},
                    {-96,-101,-98,-97,-95,-98,-100,-100},
                    {-100,-102,-105,-91,-99,-96,-95,-98},
                    {-100,-95,-94,-98,-101,-98,-96,-95},
                    {-100,-96,-100,-96,-95,-99,-95,-93}},
                    
                    {{-43,-41,-42,-46,-44,-42,-50,-46}, // -7
                    {-42,-40,-50,-44,-44,-44,-48,-43},
                    {-41,-49,-45,-43,-45,-44,-42,-41},
                    {-41,-43,-43,-42,-43,-42,-48,-47},
                    {-40,-40,-40,-41,-40,-42,-41,-42},
                    {-42,-42,-41,-39,-42,-40,-40,-41},
                    {-43,-41,-39,-40,-42,-41,-41,-38},
                    {-42,-40,-43,-41,-40,-41,-40,-39}}
        };

};