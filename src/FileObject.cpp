#include "FileObject.h"


std::mutex t_mutex;

int tReadFile(const std::string & filePath, std::vector<buffer>& buffs)
{
	std::cout << "called tReadFile \n";
	std::ifstream file(filePath);
    buffer buff;
	//m_values_mutex.lock();
    buff.push_back(filePath);
	//m_values_mutex.unlock();
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {   
		//	m_values_mutex.lock();
            buff.push_back(line);
		//	m_values_mutex.unlock();
            //std::cout << line << '\n';
        }
        file.close();
    }
    //std::lock_guard<std::mutex> lk(m_values_mutex);
	//t_mutex.lock();
    buffs.push_back(buff);
	//t_mutex.unlock();
	//m_values_mutex.unlock();
    //m_values_mutex.unlock();
    return 0;
}

int FileObject::readFile(const std::string& filePath)
{
	
    std::ifstream file(filePath);
	
    buffer buff;
	//m_values_mutex.lock();
    buff.push_back(filePath);
	//m_values_mutex.unlock();
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {   
		//	m_values_mutex.lock();
            buff.push_back(line);
		//	m_values_mutex.unlock();
            //std::cout << line << '\n';
        }
        file.close();
    }
    //std::lock_guard<std::mutex> lk(m_values_mutex);
//	m_values_mutex.lock();
    m_buffers.push_back(buff);
	//m_values_mutex.unlock();
    //m_values_mutex.unlock();
    return 0;
}

int FileObject::writeFile(const std::string& filePath)
{
    std::ofstream file(filePath);
    if (file.is_open())
    {
        
    }
    
    return 0;
}

int FileObject::loadFromDirectory(const char * name, int level)
	{
		std::cout << "scan on " << name << "\n";
		DIR *dir;
		struct dirent *entry;

		if (!(dir = opendir(name)))
		{
			std::cout << "dir failed \n";
			return 0;
		}

		if (!(entry = readdir(dir)))
		{
			std::cout << "entry failed \n";
			return 0;
		}	


		do {
			if (entry->d_type == DT_DIR) {
				char path[1024];
				int len = _snprintf_s(path, sizeof(path) - 1, "%s/%s", name, entry->d_name);
				path[len] = 0;
				if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
					continue;
					//printf("%*s[%s]\n", level * 2, "", entry->d_name);
				loadFromDirectory(path, level + 1);
			}
			else
			{
				//printf("%*s- %s\n", level * 2, "", entry->d_name);
				std::string texturePath = name;
				texturePath.append("/");
				texturePath.append(entry->d_name);

				if (texturePath.find("Packets/") != std::string::npos)
				{
					if (texturePath.find(".xml") != std::string::npos)
					{
						std::cout << "packet " << entry->d_name << " found " << count << "\n";
                        
						//m_threads.emplace_back(&FileObject::readFile,this, texturePath.c_str());
						//if(count == 0 )
						//{
							//std::thread t(&FileObject::readFile,this, texturePath.c_str());
							//t.join();
							//std::thread t(tReadFile, texturePath.c_str(),std::ref(m_buffers));
							//t.detach();
							std::thread t (&FileObject::readFile,this, texturePath.c_str());
							t.join();
							count++;
						//}
						
						//t.join();
                       // m_threads.push_back(std::thread(tReadFile, texturePath.c_str(),std::ref(m_buffers)));
                        //readFile(texturePath);
						//loadSpritePacket(texturePath.c_str());
					}
				}

			}
		} while (entry = readdir(dir));
		closedir(dir);
		return 0;
	}


void FileObject::executeRead()
{
	
	
	unsigned int n = std::thread::hardware_concurrency();
	m_buffers.reserve(n);
	m_buffers.resize(n);
	std::cout << "total thread can be run is " << n << "\n";
    std::cout << "total threads " << m_threads.size() << "\n";
    // for(int i = 0; i < 2; ++i)
	// {

	// 	m_threads[i].join();
		
    // }
	//m_threads[0].join();
    std::cout << "total buffers " << m_buffers.size() << "\n";
}

void FileObject::displayData()
{
    int count = 0;
    for(auto& buff : m_buffers)
    {
        
        std::cout << "buffer index " << count++ << "\n";
        for(auto& line : buff)
        {
            std::cout << line << "\n";
        }
    }
}

FileObject::FileObject()
{
	m_buffers.clear();
}

FileObject::~FileObject()
{
 //std::cout << "total buffers " << m_buffers.size() << "\n";
}