#include<iostream>
#include<vector>
#include<string>

class Model {
private:
	std::string name,version;
	double accuracy;
	std::string created_at;
	std::string description;
public:
	Model() = default;

	Model(const std::string& n,const std::string& v, double a,const std::string& c,const std::string& d)
		:name(n), version(v), accuracy(a), created_at(c), description(d) {}

	std::string getName() const { return name; }
	std::string getVersion() const { return version; }
	double getAccuracy() const { return accuracy; }
	std::string getCreated_at() const { return created_at; }
	std::string getDescription()const { return description; }

	void setVersion(const std::string& v) { version = v; }
	void setAccuracy(double a) { accuracy = a; }
	void setDescription(const std::string& d) { description = d; }

	~Model(){}
};

class Manager {
private:
	std::vector <Model> models;
public:
	void addModel(const Model& model) {
		models.push_back(model);
	}

	bool removeModel(const std::string& name) {
		for (auto t=models.begin();t!=models.end();++t) {
			if (t->getName() == name) {
				models.erase(t);
				return true;
			}
		}
		return false;
	}

	bool updateModel(const std::string& name, const Model& newModel) {
		for (auto& t : models) {
			if (t.getName() == name) {
				t = newModel;
				return true;
			}
		}
		return false;
	}

	Model* findModel(const std::string& name) {
		for (auto& t : models) {
			if (t.getName() == name) {
				return &t;
			}
		}
		return nullptr;
	}

	void listModels() const{
		for (const auto& t : models) {
			std::cout << "Name: " << t.getName()
				<< "\nVersion: " << t.getVersion()
				<< "\nAccuracy: " << t.getAccuracy()
				<< "\nCreated at: " << t.getCreated_at()
				<< "\nDescription: " << t.getDescription()
				<< "\n\n";
		}
	}

	void menu() {
		int choice;
		do {
			std::cout<<"====MENU===="
				<< "\n1.Add model"
				<< "\n2.Remove model"
				<< "\n3.Update metrics"
				<< "\n4.Find model"
				<< "\n5.List all models"
				<< "\n6.Exit" 
				<< "\nEnter your choice: "
				<< std::endl;
			std::cin >> choice;

			switch (choice) {
			case 1: {
				std::string name, created_at, description,version;
				double accuracy;

				std::cout << "Enter name: " << std::endl;
				std::getline(std::cin >> std::ws, name);
				std::cout << "Enter version: " << std::endl;
				std::getline(std::cin>>std::ws, version);
				std::cout << "Enter accuracy: " << std::endl;
				std::cin >> accuracy;
				std::cin.ignore();
				std::cout << "Enter created_at: " << std::endl;
				std::getline(std::cin>>std::ws, created_at);
				std::cout << "Enter description: " << std::endl;
				std::getline(std::cin>>std::ws, description);

				addModel(Model(name, version, accuracy, created_at, description));
				std::cout << "Model added successfully!\n\n";
				break;
			}
			case 2: {
				std::string name;

				std::cout << "Enter model name to remove: " << std::endl;
				std::cin >> name;

				if (removeModel(name)) {
					std::cout << "Model removed successfully!\n";
				}
				else std::cout << "Model not found!\n";
				break;
			}
			case 3: {
				std::string name, description,version;
				double accuracy;

				std::cout << "Enter name to update: " << std::endl;
				std::cin >> name;
				std::cin.ignore();
				std::cout << "Enter new version: " << std::endl;
				std::getline(std::cin>>std::ws, version);
				std::cout << "Enter new accuracy: " << std::endl;
				std::cin >> accuracy;
				std::cin.ignore();
				std::cout << "Enter new description: " << std::endl;
				std::getline(std::cin>>std::ws, description);
				
				Model* existing = nullptr;
				for (auto& t : models) {
					if (t.getName() == name) {
						existing = &t;
						break;
					}
				}

				if (existing) {
					Model updated(name, version, accuracy, existing->getCreated_at(), description);
					if (updateModel(name, updated)) std::cout << "Updated successfully.\n";
				}
				else std::cout << "Model not found.\n";
				break;
			}
			case 4: {
				std::string name;
				std::cout << "Enter name to find: " << std::endl;
				std::cin >> name;

				Model* m = findModel(name);
				if (m) {
					std::cout << "Found Model:\n"
						<< "\nName: " << m->getName()
						<< "\nVersion: " << m->getVersion()
						<< "\nAccuracy: " << m->getAccuracy()
						<< "\nDescription: " << m->getDescription()
						<< std::endl;
				}
				else std::cout << "Model not found.\n";
				break;
			}
			case 5:
				listModels();
				break;
			case 6:
				std::cout << "Exiting the program...\n";
				break;
			default:
				std::cout << "Invalid choice! Please try again.\n";
			}
		} while (choice != 6);
	}
};

int main() {
	Manager manager;
	manager.menu(); 
}
