#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;


struct Email {
    string from;
    string to;
    string body;
};


class Worker {
public:
    virtual ~Worker() = default;
    virtual void Process(unique_ptr<Email> email) = 0;
    virtual void Run() {
        // только первому worker-у в пайплайне нужно это имплементировать
        throw logic_error("Unimplemented");
    }

protected:
    // реализации должны вызывать PassOn, чтобы передать объект дальше
    // по цепочке обработчиков
    void PassOn(unique_ptr<Email> email) const {
        if (next_) {
            next_->Process(move(email));
        }
    }

public:
    void SetNext(unique_ptr<Worker> next) {
        if (!next_) {
            next_ = move(next);
        }
        else {
            next_->SetNext(move(next));
        }
    }
private:
    unique_ptr<Worker> next_;
};


class Reader : public Worker {
public:
    Reader(istream& is) : input(is) {}

    void Run() override {
        while (input) {
            Email to_process;

            if (getline(input, to_process.from)
                && getline(input, to_process.to)
                && getline(input, to_process.body)) 
            {
                PassOn(make_unique<Email>(move(to_process)));
            }

        }
    }

    void Process(unique_ptr<Email> email) override {
        //Run();
    }
private:
    istream& input;
};


class Filter : public Worker {
public:
    using Function = function<bool(const Email&)>;

    Filter(Function f) : func_(f) {}

    void Process(unique_ptr<Email> email) override {
        if (email) {
            if (func_(*email)) {
                PassOn(move(email));
            }
        }
    }

private:
    Function func_;
};


class Copier : public Worker {
public:
    Copier(string rec) : recipient_(move(rec)) {}

    void Process(unique_ptr<Email> email) override {
        unique_ptr<Email> new_email;
        if (email->to != recipient_) {
            new_email = make_unique<Email>(Email{ email->from, recipient_ , email->body });
        }
        PassOn(move(email));

        if (new_email) {
            PassOn(move(new_email));
        }
    }
private:
    string recipient_;
};


class Sender : public Worker {
public:
    Sender(ostream& os) : output(os) {}

    void Process(unique_ptr<Email> email) override {
        output << email->from << '\n'
               << email->to << '\n'
               << email->body << '\n';

        PassOn(move(email));
    }

private:
    ostream& output;
};


// реализуйте класс
class PipelineBuilder {
public:
    // добавляет в качестве первого обработчика Reader
    explicit PipelineBuilder(istream& in) {
        head_ = make_unique<Reader>(in);
    }

    // добавляет новый обработчик Filter
    PipelineBuilder& FilterBy(Filter::Function filter) {
        head_->SetNext(make_unique<Filter>(filter));
        return *this;
    }

    // добавляет новый обработчик Copier
    PipelineBuilder& CopyTo(string recipient) {
        head_->SetNext(make_unique<Copier>(recipient));
        return *this;
    }

    // добавляет новый обработчик Sender
    PipelineBuilder& Send(ostream& out) {
        head_->SetNext(make_unique<Sender>(out));
        return *this;
    }
    // возвращает готовую цепочку обработчиков
    unique_ptr<Worker> Build() {
        return move(head_);
    }
private:
    unique_ptr<Worker> head_;
};


void TestSanity() {
    string input = (
        "erich@example.com\n"
        "richard@example.com\n"
        "Hello there\n"

        "erich@example.com\n"
        "ralph@example.com\n"
        "Are you sure you pressed the right button?\n"

        "ralph@example.com\n"
        "erich@example.com\n"
        "I do not make mistakes of that kind\n"
        );
    istringstream inStream(input);
    ostringstream outStream;

    PipelineBuilder builder(inStream);
    builder.FilterBy([](const Email& email) {
        return email.from == "erich@example.com";
    });
    builder.CopyTo("richard@example.com");
    builder.Send(outStream);
    auto pipeline = builder.Build();

    pipeline->Run();

    string expectedOutput = (
        "erich@example.com\n"
        "richard@example.com\n"
        "Hello there\n"

        "erich@example.com\n"
        "ralph@example.com\n"
        "Are you sure you pressed the right button?\n"

        "erich@example.com\n"
        "richard@example.com\n"
        "Are you sure you pressed the right button?\n"
        );

    ASSERT_EQUAL(expectedOutput, outStream.str());
}

//int main() {
//    TestRunner tr;
//    RUN_TEST(tr, TestSanity);
//    return 0;
//}
