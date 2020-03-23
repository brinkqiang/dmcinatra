/********************************************************************
**       This cc file is generated by program,                   **
**            Please do not change it directly.                    **
**                   Auther: brinkqiang                            **
********************************************************************/
// source: msgperformance.proto

#include "msgperformance.cf.h"

CDMCF_msgperformance::CDMCF_msgperformance()
{

}

CDMCF_msgperformance::~CDMCF_msgperformance()
{

}

bool CDMCF_msgperformance::FillTemplateFile(const std::string& strPath)
{

    {
        ::msgperformance::dmnode_xmsg map_xmsg;
        GetMeta().mutable_map_xmsg()->insert({ { map_xmsg.msgid(), map_xmsg } });
    }

    SaveJSON(strPath.empty() ? GetTplPath() : strPath);
    SaveCSV(strPath.empty() ? GetTplPath() : strPath);
    SaveXML(strPath.empty() ? GetTplPath() : strPath);
    SaveXLSX(strPath.empty() ? GetTplPath() : strPath);
    SaveMD(strPath.empty() ? GetTplPath() : strPath);
    return true;
}

std::string CDMCF_msgperformance::FormatMDHeader(std::vector<std::string>& vecList)
{
    std::stringstream ss;

    for (int i=0; i < vecList.size(); ++i)
    {
        ss << CONFIG_MD_DELIM << "";
    }

    ss << CONFIG_MD_DELIM << std::endl;

    for (int i = 0; i < vecList.size(); ++i)
    {
        ss << CONFIG_MD_DELIM << ":--:";
    }

    ss << CONFIG_MD_DELIM << std::endl;

    for (int i = 0; i < vecList.size(); ++i)
    {
        ss << CONFIG_MD_DELIM << "**" << vecList[i] << "**";
    }

    ss << CONFIG_MD_DELIM << std::endl;

    return ss.str();
}

bool CDMCF_msgperformance::SaveMD(const std::string & strPath)
{

    if (!SaveMD_map_xmsg(strPath.empty() ? GetPath() : strPath))
    {
        goto FAIL;
    }

    return true;
FAIL:
    OnError(GetLastErrorData());
    return false;
}


bool CDMCF_msgperformance::SaveMD_map_xmsg(const std::string& strPath)
{
    std::string strFile = fmt::format("{}{}{}", strPath.empty() ? GetPath() : strPath, CONFIG_PATH_DELIMITER, "msgperformance.map_xmsg.md");

    std::ofstream fs;
    LOCAL_GUARD(fs.open(strFile.c_str()));
    if (fs.fail())
    {
        LastErrorData() << "file: msgperformance.map_xmsg.md can't load. please check file path & file attribute.";
        goto FAIL;
    }

    GetMDDoc_map_xmsg(fs);
    return true;
FAIL:
    OnError(GetLastErrorData());
    return false;
}



std::ostream& CDMCF_msgperformance::GetMDDoc_map_xmsg(std::ostream& os)
{
    std::stringstream ss;
    WriteCSVHeader_dmnode_xmsg(ss, "", CONFIG_CSV_DELIM);
    std::vector<std::string> vecList;
    strtk::parse(ss.str(), ",", vecList);

    os << FormatMDHeader(vecList);

    for (auto it = GetMeta().map_xmsg().begin(); it != GetMeta().map_xmsg().end(); ++it)
    {
        os << CONFIG_MD_DELIM;
        WriteCSV_dmnode_xmsg(os, it->second, CONFIG_MD_DELIM);
        os << CONFIG_MD_DELIM << std::endl;
    }
    return os;
}


bool CDMCF_msgperformance::LoadJSON(const std::string& strPath)
{
    std::string strFile = fmt::format("{}{}{}", strPath.empty() ? GetPath() : strPath, CONFIG_PATH_DELIMITER, "msgperformance.json");
    std::ifstream fs;
    LOCAL_GUARD(fs.open(strFile));
    if (fs.fail())
    {
        if (CONFIG_FILE_NOTEXIST) return true;
        OnError("file: msgperformance.json can't load. please check file path & file attribute.\n");
        return false;
    }
    std::stringstream ss;
    ss << fs.rdbuf();
    google::protobuf::util::JsonStringToMessage(ss.str(), &GetMeta());

    return true;
}

bool CDMCF_msgperformance::SaveJSON(const std::string& strPath)
{
    std::string strFile = fmt::format("{}{}{}", strPath.empty() ? GetPath() : strPath, CONFIG_PATH_DELIMITER, "msgperformance.json");
    std::ofstream fs;
    LOCAL_GUARD(fs.open(strFile));
    if (fs.fail())
    {
        if (CONFIG_FILE_NOTEXIST) return true;
        OnError("file: msgperformance.json can't load. please check file path & file attribute.\n");
        return false;
    }
    std::string strJson;
    google::protobuf::util::MessageToJsonString(GetMeta(), &strJson);
    fs << strJson;

    return true;
}

bool CDMCF_msgperformance::LoadXLSX(const std::string& strPath)
{
    try
    {
        std::string strFile = fmt::format("{}{}{}", strPath.empty() ? GetPath() : strPath, CONFIG_PATH_DELIMITER, "msgperformance.xlsx");
        XLDocument doc;
        doc.OpenDocument(strFile);
    
        auto map_xmsg = doc.Workbook().Worksheet("map_xmsg");
    
    
        for (int i = 3; i <= map_xmsg.RowCount(); ++i)
        {
            int j = 1;
            ::msgperformance::dmnode_xmsg node;
            ReadXLSX_dmnode_xmsg(node, i, j, map_xmsg);

            if (GetMeta().mutable_map_xmsg()->find(node.msgid()) != GetMeta().mutable_map_xmsg()->end())
            {
                OnError("dmnode_xmsg.msgid() = [" + fmt::to_string(node.msgid()) + "] repeat");
                continue;
            }

            GetMeta().mutable_map_xmsg()->insert({ { node.msgid(), node} });
        }
    
    }
    catch(std::runtime_error& e)
    {
        OnError(e.what());
        return false;
    }

    return true;
}

bool CDMCF_msgperformance::SaveXLSX(const std::string& strPath)
{
    try
    {
        std::string strFile = fmt::format("{}{}{}", strPath.empty() ? GetPath() : strPath, CONFIG_PATH_DELIMITER, "msgperformance.xlsx");
        XLDocument doc;
        doc.CreateDocument(strFile);
    
        doc.Workbook().AddWorksheet("map_xmsg");
    
        if (doc.Workbook().WorksheetExists("Sheet1"))
        {
            doc.Workbook().DeleteSheet("Sheet1");
        }
    
        auto map_xmsg = doc.Workbook().Worksheet("map_xmsg");
    
    
        SaveXLSX_map_xmsg(map_xmsg);
    

        doc.SaveDocument();
    }
    catch(std::runtime_error& e)
    {
        OnError(e.what());
        return false;
    }

    return true;
}

void CDMCF_msgperformance::WriteXLSXHeader_dmnode_xmsg(int index, XLWorksheet& sheet)
{
    std::stringstream ss;
    WriteCSVHeader_dmnode_xmsg(ss, "", CONFIG_CSV_DELIM);
    std::vector<std::string> vecList;
    strtk::parse(ss.str(), ",", vecList);
    
    for (int i=0; i < vecList.size(); ++i)
    {
        sheet.Cell(index, i+1).Value() = vecList[i];
    }
}
void CDMCF_msgperformance::WriteXLSXHeader_dmnode_xtotal(int index, XLWorksheet& sheet)
{
    std::stringstream ss;
    WriteCSVHeader_dmnode_xtotal(ss, "", CONFIG_CSV_DELIM);
    std::vector<std::string> vecList;
    strtk::parse(ss.str(), ",", vecList);
    
    for (int i=0; i < vecList.size(); ++i)
    {
        sheet.Cell(index, i+1).Value() = vecList[i];
    }
}

void CDMCF_msgperformance::ReadXLSX_dmnode_xmsg(::msgperformance::dmnode_xmsg& node, int& i, int& j, XLWorksheet& sheet)
{
    node.set_msgid(sheet.Cell(i, j++).Value().Get<::google::protobuf::uint32>());
    node.set_maxconsumetime(sheet.Cell(i, j++).Value().Get<::google::protobuf::uint64>());
    node.set_avgconsumetime(sheet.Cell(i, j++).Value().Get<::google::protobuf::uint64>());
    node.set_totalconsumetime(sheet.Cell(i, j++).Value().Get<::google::protobuf::uint64>());
    node.set_msgcount(sheet.Cell(i, j++).Value().Get<::google::protobuf::uint64>());
    node.set_totalmsgsize(sheet.Cell(i, j++).Value().Get<::google::protobuf::uint64>());
    node.set_lasttime(sheet.Cell(i, j++).Value().Get<::std::string>());
    
}
void CDMCF_msgperformance::ReadXLSX_dmnode_xtotal(::msgperformance::dmnode_xtotal& node, int& i, int& j, XLWorksheet& sheet)
{
    node.set_totalsize(sheet.Cell(i, j++).Value().Get<::google::protobuf::uint64>());
    
}

void CDMCF_msgperformance::WriteXLSX_dmnode_xmsg(::msgperformance::dmnode_xmsg& node, int& i, int& j, XLWorksheet& sheet)
{
    sheet.Cell(i, j++).Value() = node.msgid();
    sheet.Cell(i, j++).Value() = node.maxconsumetime();
    sheet.Cell(i, j++).Value() = node.avgconsumetime();
    sheet.Cell(i, j++).Value() = node.totalconsumetime();
    sheet.Cell(i, j++).Value() = node.msgcount();
    sheet.Cell(i, j++).Value() = node.totalmsgsize();
    sheet.Cell(i, j++).Value() = node.lasttime();
    
}
void CDMCF_msgperformance::WriteXLSX_dmnode_xtotal(::msgperformance::dmnode_xtotal& node, int& i, int& j, XLWorksheet& sheet)
{
    sheet.Cell(i, j++).Value() = node.totalsize();
    
}


void CDMCF_msgperformance::SaveXLSX_map_xmsg(XLWorksheet& sheet)
{
    WriteXLSXHeader_dmnode_xmsg(1, sheet);
    WriteXLSXHeader_dmnode_xmsg(2, sheet);

    int i = 3;
    for (auto it = GetMeta().mutable_map_xmsg()->begin(); it != GetMeta().mutable_map_xmsg()->end(); ++it, ++i)
    {
        int j = 1;
        WriteXLSX_dmnode_xmsg((it->second), i, j, sheet);
    }
}


bool CDMCF_msgperformance::LoadCSV(const std::string& strPath)
{

    if (!LoadCSV_map_xmsg(strPath.empty() ? GetPath() : strPath))
    {
        goto FAIL;
    }


    return true;
FAIL:
    return false;
}

bool CDMCF_msgperformance::SaveCSV(const std::string& strPath)
{

    if (!SaveCSV_map_xmsg(strPath.empty() ? GetPath() : strPath))
    {
        goto FAIL;
    }

    return true;
FAIL:
    OnError(GetLastErrorData());
    return false;
}


bool CDMCF_msgperformance::LoadCSV_map_xmsg(const std::string& strPath)
{
    std::string strFile = fmt::format("{}{}{}", strPath.empty() ? GetPath() : strPath, CONFIG_PATH_DELIMITER, "msgperformance.map_xmsg.csv");
    
    try
    {
        csv::CSVReader reader(strFile);
        csv::CSVRow row;
        if(DM_SKIP_CSV_FIRST_COW){ reader.read_row(row);}
        for (size_t i = 1; reader.read_row(row); i++)
        {
            int j = 0;
            ::msgperformance::dmnode_xmsg node;
            ReadCSV_dmnode_xmsg(node, j, row);

            if (GetMeta().mutable_map_xmsg()->find(node.msgid()) != GetMeta().mutable_map_xmsg()->end())
            {
                OnError("dmnode_xmsg.msgid() = [" + fmt::to_string(node.msgid()) + "] repeat");
                continue;
            }

            GetMeta().mutable_map_xmsg()->insert({ { node.msgid(), node} });
        }
    }
    catch (std::runtime_error& e)
    {
        OnError(e.what());
        return false;
    }

    return true;
}


bool CDMCF_msgperformance::SaveCSV_map_xmsg(const std::string& strPath)
{
    std::string strFile = fmt::format("{}{}{}", strPath.empty() ? GetPath() : strPath, CONFIG_PATH_DELIMITER, "msgperformance.map_xmsg.csv");

    std::ofstream fs;
    LOCAL_GUARD(fs.open(strFile.c_str()));
    if (fs.fail())
    {
        LastErrorData() << "file: msgperformance.map_xmsg.csv can't load. please check file path & file attribute.";
        goto FAIL;
    }

    GetCSVDoc_map_xmsg(fs);
    return true;
FAIL:
    OnError(GetLastErrorData());
    return false;
}


std::ostream& CDMCF_msgperformance::GetCSVDoc_map_xmsg(std::ostream& os)
{
    WriteCSVHeader_dmnode_xmsg(os, "", CONFIG_CSV_DELIM);
    os << std::endl;
    if(DM_SKIP_CSV_FIRST_COW)
    {
        WriteCSVHeader_dmnode_xmsg(os, "", CONFIG_CSV_DELIM);
        os << std::endl;           
    }

    for (auto it = GetMeta().map_xmsg().begin(); it != GetMeta().map_xmsg().end(); ++it)
    {
        WriteCSV_dmnode_xmsg(os, it->second, CONFIG_CSV_DELIM);
        os << std::endl;
    }
    return os;
}


void CDMCF_msgperformance::ReadCSV_dmnode_xmsg(::msgperformance::dmnode_xmsg& node, int& j, csv::CSVRow& row)
{
    node.set_msgid(row[j++].get<::google::protobuf::uint32>());
    node.set_maxconsumetime(row[j++].get<::google::protobuf::uint64>());
    node.set_avgconsumetime(row[j++].get<::google::protobuf::uint64>());
    node.set_totalconsumetime(row[j++].get<::google::protobuf::uint64>());
    node.set_msgcount(row[j++].get<::google::protobuf::uint64>());
    node.set_totalmsgsize(row[j++].get<::google::protobuf::uint64>());
    node.set_lasttime(row[j++].get<::std::string>());
    
}
void CDMCF_msgperformance::ReadCSV_dmnode_xtotal(::msgperformance::dmnode_xtotal& node, int& j, csv::CSVRow& row)
{
    node.set_totalsize(row[j++].get<::google::protobuf::uint64>());
    
}

void CDMCF_msgperformance::WriteCSV_dmnode_xmsg(std::ostream& os, const ::msgperformance::dmnode_xmsg& node, const std::string& delim)
{
    
    os << node.msgid();
    os << delim;
    os << node.maxconsumetime();
    os << delim;
    os << node.avgconsumetime();
    os << delim;
    os << node.totalconsumetime();
    os << delim;
    os << node.msgcount();
    os << delim;
    os << node.totalmsgsize();
    os << delim;
    os << node.lasttime();
    
}
void CDMCF_msgperformance::WriteCSV_dmnode_xtotal(std::ostream& os, const ::msgperformance::dmnode_xtotal& node, const std::string& delim)
{
    
    os << node.totalsize();
    
}

void CDMCF_msgperformance::WriteCSVHeader_dmnode_xmsg(std::ostream& os, const std::string& name, const std::string& delim)
{
    
    os << (name.empty() ? "" : name + ".") << "msgid";
    os << delim;
    os << (name.empty() ? "" : name + ".") << "maxconsumetime";
    os << delim;
    os << (name.empty() ? "" : name + ".") << "avgconsumetime";
    os << delim;
    os << (name.empty() ? "" : name + ".") << "totalconsumetime";
    os << delim;
    os << (name.empty() ? "" : name + ".") << "msgcount";
    os << delim;
    os << (name.empty() ? "" : name + ".") << "totalmsgsize";
    os << delim;
    os << (name.empty() ? "" : name + ".") << "lasttime";
    
}
void CDMCF_msgperformance::WriteCSVHeader_dmnode_xtotal(std::ostream& os, const std::string& name, const std::string& delim)
{
    
    os << (name.empty() ? "" : name + ".") << "totalsize";
    
}

bool CDMCF_msgperformance::LoadXML(const std::string& strPath)
{
    std::string strFile = fmt::format("{}{}{}", strPath.empty() ? GetPath() : strPath, CONFIG_PATH_DELIMITER, "msgperformance.xml");

    std::ifstream fs;
    LOCAL_GUARD(fs.open(strFile));
    if (fs.fail())
    {
        if (CONFIG_FILE_NOTEXIST) return true;
        OnError("file: msgperformance.xml can't load. please check file path & file attribute.\n");
        return false;
    }

    std::string strDoc((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
    if (!SetXMLDoc(strDoc))
    {
        LastErrorData() << "file: msgperformance.xml can't parser. please check file info.\n";
        goto FAIL;
    }

    return true;
FAIL:
    OnError(GetLastErrorData());
    return false;
}

bool CDMCF_msgperformance::SaveXML(const std::string& strPath)
{
    std::string strFile = fmt::format("{}{}{}", strPath.empty() ? GetPath() : strPath, CONFIG_PATH_DELIMITER, "msgperformance.xml");

    std::ofstream fs;
    LOCAL_GUARD(fs.open(strFile.c_str()));
    if (fs.fail())
    {
        if (CONFIG_FILE_NOTEXIST) return true;
        LastErrorData() << "file: msgperformance.xml can't load. please check file path & file attribute.\n";
        goto FAIL;
    }

    GetXMLDoc(fs);
    return true;
FAIL:
    OnError(GetLastErrorData());
    return false;
}

bool CDMCF_msgperformance::SetXMLDoc(const std::string& strDoc)
{
    pugi::xml_document doc;
    if (!doc.load_buffer(strDoc.c_str(), strDoc.size()))
    {
        return false;
    }

    pugi::xml_node datas = doc.child("msgperformance");
    if (!datas)
    {
        return false;
    }

    LoadXML_map_xmsg(datas);

    return true;
}

std::ostream& CDMCF_msgperformance::GetXMLDoc(std::ostream& os)
{
    pugi::xml_document doc;
    pugi::xml_node msgperformance = doc.append_child("msgperformance");

    pugi::xml_node map_xmsg = msgperformance.append_child("map_xmsg");
    SaveXML_map_xmsg(map_xmsg);


    doc.save(os, DM_INDENT, DM_FLAG, DM_ENCODING);

    return os;
}

void CDMCF_msgperformance::SaveXML_map_xmsg(pugi::xml_node& map_xmsg)
{
    for (auto it = GetMeta().mutable_map_xmsg()->begin(); it != GetMeta().mutable_map_xmsg()->end(); ++it)
    {
        pugi::xml_node node = map_xmsg.append_child("dmnode_xmsg");
        WriteXML_dmnode_xmsg((it->second), node);
    }
}


void CDMCF_msgperformance::LoadXML_map_xmsg(pugi::xml_node& datas)
{
    pugi::xml_node map_xmsg = datas.child("map_xmsg");
    if (map_xmsg)
    {
        pugi::xml_object_range<pugi::xml_named_node_iterator> dmnode_xmsg = map_xmsg.children("::msgperformance::dmnode_xmsg");

        pugi::xml_named_node_iterator It = dmnode_xmsg.begin();
        int i = 0;
        for (i = 0; It != dmnode_xmsg.end(); ++i, ++It)
        {
            ::msgperformance::dmnode_xmsg node;

            ReadXML_dmnode_xmsg(node, *It);

            GetMeta().mutable_map_xmsg()->insert({ { node.msgid(), node} });
        }
    }
}


void CDMCF_msgperformance::ReadXML_dmnode_xmsg(::msgperformance::dmnode_xmsg& node, const pugi::xml_node& oXml)
{
    
    node.set_msgid(fmt::lexical_cast<::google::protobuf::uint32>(oXml.child("msgid").text().as_string()));
    
    node.set_maxconsumetime(fmt::lexical_cast<::google::protobuf::uint64>(oXml.child("maxconsumetime").text().as_string()));
    
    node.set_avgconsumetime(fmt::lexical_cast<::google::protobuf::uint64>(oXml.child("avgconsumetime").text().as_string()));
    
    node.set_totalconsumetime(fmt::lexical_cast<::google::protobuf::uint64>(oXml.child("totalconsumetime").text().as_string()));
    
    node.set_msgcount(fmt::lexical_cast<::google::protobuf::uint64>(oXml.child("msgcount").text().as_string()));
    
    node.set_totalmsgsize(fmt::lexical_cast<::google::protobuf::uint64>(oXml.child("totalmsgsize").text().as_string()));
    
    node.set_lasttime(fmt::lexical_cast<::std::string>(oXml.child("lasttime").text().as_string()));
    
}
void CDMCF_msgperformance::ReadXML_dmnode_xtotal(::msgperformance::dmnode_xtotal& node, const pugi::xml_node& oXml)
{
    
    node.set_totalsize(fmt::lexical_cast<::google::protobuf::uint64>(oXml.child("totalsize").text().as_string()));
    
}

void CDMCF_msgperformance::WriteXML_dmnode_xmsg(::msgperformance::dmnode_xmsg& node, pugi::xml_node& oXml)
{
    
    pugi::xml_node msgid = oXml.append_child("msgid");
    msgid.append_child(pugi::node_pcdata).set_value(node.msgid());
    
    pugi::xml_node maxconsumetime = oXml.append_child("maxconsumetime");
    maxconsumetime.append_child(pugi::node_pcdata).set_value(node.maxconsumetime());
    
    pugi::xml_node avgconsumetime = oXml.append_child("avgconsumetime");
    avgconsumetime.append_child(pugi::node_pcdata).set_value(node.avgconsumetime());
    
    pugi::xml_node totalconsumetime = oXml.append_child("totalconsumetime");
    totalconsumetime.append_child(pugi::node_pcdata).set_value(node.totalconsumetime());
    
    pugi::xml_node msgcount = oXml.append_child("msgcount");
    msgcount.append_child(pugi::node_pcdata).set_value(node.msgcount());
    
    pugi::xml_node totalmsgsize = oXml.append_child("totalmsgsize");
    totalmsgsize.append_child(pugi::node_pcdata).set_value(node.totalmsgsize());
    
    pugi::xml_node lasttime = oXml.append_child("lasttime");
    lasttime.append_child(pugi::node_pcdata).set_value(node.lasttime());
    
}
void CDMCF_msgperformance::WriteXML_dmnode_xtotal(::msgperformance::dmnode_xtotal& node, pugi::xml_node& oXml)
{
    
    pugi::xml_node totalsize = oXml.append_child("totalsize");
    totalsize.append_child(pugi::node_pcdata).set_value(node.totalsize());
    
}