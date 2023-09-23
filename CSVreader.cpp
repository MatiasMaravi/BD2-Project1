#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
class CSVRow{
    string         m_line;
    vector<int>    m_data;
    public:
    string_view operator[](size_t index) const;
    size_t size() const;
    void readNextRow(istream& str);

};
string_view CSVRow::operator[](size_t index) const{
    return string_view(&m_line[m_data[index] + 1], m_data[index + 1] - (m_data[index] + 1));
}
size_t CSVRow::size() const{
    return m_data.size() - 1;
}
void CSVRow::readNextRow(istream& str){
    getline(str, m_line);

    m_data.clear();
    m_data.emplace_back(-1);
    string::size_type pos = 0;
    while((pos = m_line.find(',', pos)) != string::npos)
    {
        m_data.emplace_back(pos);
        ++pos;
    }
    // This checks for a trailing comma with no data after it.
    pos   = m_line.size();
    m_data.emplace_back(pos);
}

istream& operator>>(istream& str, CSVRow& data){
    data.readNextRow(str);
    return str;
}   
int main(){
    ifstream file("archive/alumnos.csv");

    CSVRow row;
    while(file >> row)
    {
        cout << "4th Element(" << row[1] << ")\n";
    }
}