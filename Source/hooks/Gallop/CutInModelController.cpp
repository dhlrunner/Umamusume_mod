#include "CutInModelController.h"

namespace Gallop::CutInModelController
{
	void* CreateModel_orig = nullptr;
	void* CreateModel_hook(CutInModelController_Context* context) {
		printf("Called Gallop_CutInModelController_CreateModel\n");
		printf("charid=%d\n", context->CharaId);
		printf("cardid=%d\n", context->CardId);
		printf("DressID=%d\n", context->DressId);
		printf("Controllertype=%d\n", context->ControllerType);
		printf("overrideClothCategory=%d\n", context->_overrideClothCategory);

		/*Il2CppObject* EditableCharinfo = il2cpp_object_new((Il2CppClass*)il2cpp_symbols::get_class("umamusume.dll", "Gallop", "EditableCharacterBuildInfo"));

		printf("il2cppobject_new %p\n", EditableCharinfo->klass);

		auto ctor_2 = reinterpret_cast<void (*)
			(Il2CppObject * _instance, int cardId, int charaId, int dressId, int controllerType, int zekken, int mobId, int backDancerColorId, int headId, bool isUseDressDataHeadModelSubId, bool isEnableModelCache)>(il2cpp_class_get_method_from_name((Il2CppClass*)EditableCharinfo->klass, ".ctor",10)->methodPointer);

		printf("il2cppobject_new ctor_2 = %p\n", &ctor_2);

		ctor_2(EditableCharinfo, 100101, 1001, 100101, (int)context->ControllerType , 0, 0, -1, 0, true, true);

		printf("%p\n", EditableCharinfo);

		return EditableCharinfo->klass;*/

		//context->_overrideClothCategory = CySpringDataContainer::Category::Training;
		if (Settings::Local->changeStoryChar) {
			if ((Settings::Local->story3dCharID < 0) || (Settings::Local->story3dClothID < 0) || (Settings::Local->story3dHeadID < 0))
			{
				std::string line;
				while (true) {
					try {


						std::cout << "Enter charaid, clothid, headid, cardid" << line << "\n";

						std::getline(std::cin, line);

						//std::cout <<  "Entered: " << line;
						std::vector < std::string > arg = Utils::explode(line, ' ');


						int _charaId = std::stoi(arg.at(0).c_str());
						int _dressId = std::stoi(arg.at(1).c_str());
						int _headid = std::stoi(arg.at(2).c_str());
						int _cardid = std::stoi(arg.at(3).c_str());

						context->CharaId = _charaId;
						context->DressId = _dressId;
						context->HeadId = _headid;
						context->CardId = _cardid;

						printf("CutInModelController.Context set manual %d %d %d %d\n", context->CharaId, context->DressId, context->HeadId, context->CardId);
						break;
					}
					catch (std::invalid_argument&) {
						printf("Value Error: please enter number only\n");
					}
					catch (std::out_of_range&) {
						std::cout << "You entered " << line << "\n";
						printf_s("Argument Error: please enter {CharID} {Dress id} {Head ID} {Card id}\n");
					}
				}



				//printf("Enter charaid, clothid, headid, mobid: ");

				//scanf_s("%d %d %d %d", &charaId, &clothId, &headId, &mobId);
				printf("\n");
			}
			else
			{
				context->CharaId = Settings::Local->story3dCharID;
				context->DressId = Settings::Local->story3dClothID;
				context->HeadId = Settings::Local->story3dHeadID;
				printf("CutInModelController.Context set %d %d %d\n", context->CharaId, context->DressId, context->HeadId);
			}
		}
		//context->CharaId = 9004;
		return reinterpret_cast<decltype(CreateModel_hook)*>(CreateModel_orig)(context);
	}
	
	void Init()
	{
		Logger::Info(SECTION_NAME, L"Init");
		auto CreateModel_addr = reinterpret_cast<void* (*)(CutInModelController_Context*)>(
			il2cpp_symbols::get_method_pointer(
				"umamusume.dll", "Gallop",
				"CutInModelController", "CreateModel", 1
			)
		);
		EnableHook(CreateModel_addr, &CreateModel_hook, &CreateModel_orig, L"Gallop_CutInModelController_CreateModel");
		
	}
}