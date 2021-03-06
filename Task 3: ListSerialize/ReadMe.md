# Задание

Реализуйте функции сериализации и десериализации двусвязного списка в бинарном формате в файл.
<pre>
    <code>
// структуру ListNode модифицровать нельзя
struct ListNode {
     ListNode *      prev;
     ListNode *      next;
     ListNode *      rand; // указатель на произвольный элемент данного списка, либо NULL
     std::string     data;
};

class List {
public:
     void Serialize   (FILE * file);  // сохранение в файл (файл открыт с помощью fopen(path, "wb"))
     void Deserialize (FILE * file);  // загрузка из файла (файл открыт с помощью fopen(path, "rb"))

private:
     ListNode *      head;
    </code>     
</pre>

## Описание

Экземпляр ListNode сериализуется путем последовательной записи сериализованных экземпляров ListNode. 
Экземпляры ListNode записываются в следующем порядке:
1. Первым записывается самый нижний элемент списка (у этого элемента this->prev == nullptr)
2. Далее последовательно записывается каждый следующий элемент (элемент по ссылки this->next)

Каждый экземпляр ListNode сериализуется следующей последовательностью байт:
1. Адрес объекта(this): 4 байта для x86 / 8 байт для x64
2. Ссылка на rand: 4 байта для x86 / 8 байт для x64
3. Длина строки data: 4 байта для x86 / 8 байт для x64
4. Строка data в виде последовательности байт.

### Замечание
При десериализации сериалиализуемые адреса будут уже не актуальны. Они используются только как идентификаторы, чтобы 
сохранить структуру объекта. 

Так же было возможность вместо идентификаторов сохранять последовательный номер каждого 
узла. При такой реализации для записи каждого узла мы экономим 4 байта для x86 / 8 байт для x64. С другой стороны такой 
подход менее универсальный и гибкий. Так же он менее надежный при угрозе повреждения данных. Из этих соображений была
 выбрана текущая реализация. 
 
 ## Использование
 
 Команды выполняются из папки с проектом.
 Сборка и запуск:
 <pre>
     <code>
 mkdir ListSerialize
 cd ListSerialize 
 cmake ../ 
 make 
 cd test
 ./unit_tests
     </code>
 </pre>