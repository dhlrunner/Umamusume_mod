#include "StoryCharacter3D.h"

namespace Gallop::StoryCharacter3D
{
	void* LoadModel_orig = nullptr;
	void* LoadModel_hook(int charaId, int cardId,
		int clothId, int zekkenNumber, int headId, bool isWet, bool isDirt, int mobId,
		int dressColorId = 0, int charaDressColorSetId = 0,
		Il2CppString* zekkenName = nullptr, int zekkenFontStyle = 1, int color = 3, int fontColor = 1, int suitColor = 1,
		bool isUseDressDataHeadModelSubId = true, bool useCircleShadow = false) {
		printf("StoryCharacter3D_LoadModel called charaid=%d, cardid=%d, clothid=%d, headid=%d mobid=%d\n", charaId, cardId, clothId, headId, mobId);
		/*std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(0, 26);
		charaId = chars[dis(gen)];
		clothId = 5;
		headId = 0;
		printf("%d\n", charaId);*/

		//rpc->showCharSelectForm();

		if (Settings::Local->changeStoryChar)
		{
			if ((Settings::Local->story3dCharID < 0) || (Settings::Local->story3dClothID < 0) || (Settings::Local->story3dHeadID < 0) || (Settings::Local->story3dMobid < 0))
			{
				std::string line;
				while (true) {
					try {


						std::cout << "Enter charaid, clothid, headid, mobid: " << line << "\n";

						std::getline(std::cin, line);

						//std::cout <<  "Entered: " << line;
						std::vector < std::string > arg = Utils::explode(line, ' ');


						int _charaId = std::stoi(arg.at(0).c_str());
						int _dressId = std::stoi(arg.at(1).c_str());
						int _mobid = std::stoi(arg.at(2).c_str());
						int _headid = std::stoi(arg.at(3).c_str());

						charaId = _charaId;
						clothId = _dressId;
						mobId = _mobid;
						headId = _headid;

						printf("story3d set manual %d %d %d %d\n", charaId, clothId, mobId, headId);
						break;
					}
					catch (std::invalid_argument&) {
						printf("Value Error: please enter number only\n");
					}
					catch (std::out_of_range&) {
						std::cout << "You entered " << line << "\n";
						printf_s("Argument Error: please enter {CharID} {Dress id} {Mod ID} {Head id}\n");
					}
				}



				//printf("Enter charaid, clothid, headid, mobid: ");

				//scanf_s("%d %d %d %d", &charaId, &clothId, &headId, &mobId);
				printf("\n");
			}
			else
			{
				/*
				if (false) {
					//random
					std::random_device dev;
					std::mt19937 rng(dev());
					std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 113); // distribution in range [1, 6]

					unsigned char index = dist6(rng);

					charaId = charaIds[index];
					if (getProbability(30)) {
						clothId = dressIds[index];
					}
					else {
						clothId = 3;
					}
					printf("!story3d random set %d %d %d %d\n", charaId, clothId, mobId, headId);
				}
				else {
					charaId = sett->story3dCharID;
					clothId = sett->story3dClothID;
					mobId = sett->story3dMobid;
					headId = sett->story3dHeadID;
					printf("story3d set %d %d %d %d\n", charaId, clothId, mobId, headId);
				}*/

			}
		}



		/*static bool flag = false;
		charaId = 9004;
		clothId = 900401;
		headId = 0;
		flag = !flag;*/
		return reinterpret_cast<decltype(LoadModel_hook)*>
			(LoadModel_orig)(charaId, cardId, clothId, zekkenNumber, headId, isWet, isDirt, mobId, dressColorId,
				charaDressColorSetId, zekkenName, zekkenFontStyle, color, fontColor, suitColor, isUseDressDataHeadModelSubId, useCircleShadow);
	}


	void Init() 
	{
		Logger::Info(SECTION_NAME, L"Init");

		auto LoadModel_addr = reinterpret_cast<void(*)(int, int, int, int, int, bool, bool, int, int, Il2CppString*, int, int, int, int, bool, bool)> (
			il2cpp_symbols::get_method_pointer(
				"umamusume.dll", "Gallop",
				"StoryCharacter3D", "LoadModel", 16 + 1
			)
		);
		EnableHook(LoadModel_addr, &LoadModel_hook, &LoadModel_orig, L"StoryCharacter3D_LoadModel");
	}
}