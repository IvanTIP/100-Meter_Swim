#include<iostream>
#include <thread>
#include<vector>
#include<mutex>

class Swimmer {
private:
    std::string name = "unknown";
    int speed = 0;
    int distance = 0;
    int time = 0;
public:
    void setName (std::string inName) {
        name = inName;
    }

    void setSpeed (int inSpeed) {
        speed = inSpeed;
    }

    void setDistance (int inDist) {
        distance = inDist;
    }

    void setTime (int inTime) {
        time = inTime;
    }

    void setData (std::vector<Swimmer*> &swimmers, int time, std::vector<std::string> &res, int num) {
        std::mutex access;
        for (int i = 0;swimmers[num] != nullptr;i++) {
            int dist;
            dist = speed * time;
            setDistance(dist);
            setTime(time);
            time++;
            access.lock();
            if (dist >= 100) {
                std::cout << name << " finished" << std::endl;
                record(res);
                delete swimmers[num];
                swimmers[num] = nullptr;
            } else {
                show();
            }
            access.unlock();
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

void createThreads (std::vector<Swimmer*> &swimmers, std::vector<std::string> &res, int &time) {
    std::thread sw1 (&Swimmer::setData,swimmers[0], std::ref(swimmers), time, std::ref(res), 0);
    std::thread sw2 (&Swimmer::setData,swimmers[1], std::ref(swimmers), time, std::ref(res), 1);
    std::thread sw3 (&Swimmer::setData,swimmers[2], std::ref(swimmers), time, std::ref(res),  2);
    std::thread sw4 (&Swimmer::setData,swimmers[3], std::ref(swimmers), time, std::ref(res), 3);
    std::thread sw5 (&Swimmer::setData,swimmers[4], std::ref(swimmers), time, std::ref(res), 4);
    std::thread sw6 (&Swimmer::setData,swimmers[5], std::ref(swimmers), time, std::ref(res), 5);
    sw1.join();
    sw2.join();
    sw3.join();
    sw4.join();
    sw5.join();
    sw6.join();
}

int main()
{
    std::vector<std::string> res;
    std::vector<Swimmer*> swimmers;
    int time = 0;
    initSwimmers(swimmers);
    createThreads(swimmers, res, time);
    showResult(res);
    return 0;
}