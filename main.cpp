#include<iostream>
#include <thread>
#include<vector>
#include<mutex>

std::mutex access;

class Swimmer {
private:
    std::string name = "unknown";
    int speed = 0;
    int distance = 0;
    int time = 0;
public:
    void setName (std::string &inName) {
        name = inName;
    }

    void setSpeed (int inSpeed) {
        speed = inSpeed;
    }

    void setData (std::vector<Swimmer*> &swimmers, std::vector<std::string> &res) {
        while (true) {
            distance = speed * time;
            time++;
            if (distance >= 100) {
                std::cout << name << " finished" << std::endl;
                access.lock();
                record(res);
                access.unlock();
                break;
            } else {
                show();
            }
        }
    }

    void show () {
        std::cout << name << ": " << distance << " m" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    void record (std::vector<std::string> &res) {
        res.push_back(name);
        res.push_back(std::to_string(time));
    }
};

void showResult (std::vector<std::string> &res) {
    std::cout << std::endl << "RESULT:" << std::endl;
    for (int i = 0;i < 12;i += 2) {
        std::cout << res[i] << ": " << res[i + 1]  << " seconds" << std::endl;
    }
}

void initSwimmers (std::vector<Swimmer*> &swimmers) {
    for (int i = 0;i < 6;i++) {
        swimmers.push_back (new Swimmer);
        std::string name;
        int speed;
        std::cout << "Enter the name: ";
        std::cin >> name;
        swimmers[i]->setName(name);
        std::cout << "Enter the speed: ";
        std::cin >> speed;
        swimmers[i]->setSpeed(speed);
    }
}

void createThreads (std::vector<Swimmer*> &swimmers, std::vector<std::string> &res) {

    std::thread sw1 (&Swimmer::setData,swimmers[0], std::ref(swimmers), std::ref(res));
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::thread sw2 (&Swimmer::setData,swimmers[1], std::ref(swimmers), std::ref(res));
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::thread sw3 (&Swimmer::setData,swimmers[2], std::ref(swimmers), std::ref(res));
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::thread sw4 (&Swimmer::setData,swimmers[3], std::ref(swimmers), std::ref(res));
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::thread sw5 (&Swimmer::setData,swimmers[4], std::ref(swimmers), std::ref(res));
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::thread sw6 (&Swimmer::setData,swimmers[5], std::ref(swimmers), std::ref(res));
    sw1.join();
    sw2.join();
    sw3.join();
    sw4.join();
    sw5.join();
    sw6.join();
}

void clear (std::vector<Swimmer*> &swimmers) {
    for (int i = 0;i < 6;i++) {
        delete swimmers[i];
        swimmers[i] = nullptr;
    }
}

int main()
{
    std::vector<std::string> res;
    std::vector<Swimmer*> swimmers;
    initSwimmers(swimmers);
    createThreads(swimmers, res);
    showResult(res);
    clear(swimmers);
    return 0;
}