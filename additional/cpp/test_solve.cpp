#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "solve.h"

TEST_CASE("JAMS RUNTIME TEST", "[jams]")
{
    std::map<std::string, std::string> jams =
        {
            {"jam01", "bb...g\na..c.g\naxxc.g\na..c..\ne...ff\ne.ddd."},
            {"jam02", "a..eee\na..f.j\nxx.fgj\nbbb.gj\n..d.hh\nccdii."},
            {"jam03", "......\n......\n.xxb..\n.aab.e\n.c.b.e\n.cdd.e"},
            {"jam04", "c..e..\nc..e..\ncxxe..\n..abbb\n..a..d\n..fffd"},
            {"jam05", "aa.e.f\nj..ebf\njxxebi\njgggbi\nd...hh\nd...cc"},
            {"jam06", "aa.f..\ngg.fej\n.xxbej\nddhbej\nc.hb..\nc..iii"},
            {"jam07", ".aeefd\n.a.gfd\n.xxg.c\n..hh.c\n...b..\n...b.."},
            {"jam08", "...aae\n..ffge\nxxdhge\nccdhii\nkkljjj\nmmlbbb"},
            {"jam09", ".affgg\n.a.dhh\nxx.dec\njbbbec\nj.i.ek\nj.i..k"},
            {"jam10", "aaf.gg\nddf..e\njxx..e\njbbb.e\nj..hcc\nii.hkk"},
            {"jam11", "daag..\nd..g..\ndxxg..\n..ebbb\n..e..f\n..cccf"},
            {"jam12", "aee..d\na.g..d\nxxg..d\n..gbbb\n....f.\nccc.f."},
            {"jam13", "aaffg.\n..d.ge\n.hdxxe\njh.cce\nj..ibb\njkkill"},
            {"jam14", "aaf...\n..f.gg\ndhxxci\ndhkkci\n..j.bb\neej..."},
            {"jam15", ".aaff.\nggddej\nbkxxej\nbkhcej\nbkhcii\n.llmm."},
            {"jam16", "aaffge\nd.hhge\ndcjxxe\n.cjbbb\n..j...\nii...."},
            {"jam17", "aeee..\na.ffgg\nxxd...\nhhdj..\nbbbjci\nkkkjci"},
            {"jam18", "aafe..\nggfe..\nhxxe..\nhbbb..\nhdd...\nccc..."},
            {"jam19", "..aee.\n..a.f.\n.cxxf.\n.cggb.\n.dddb.\n......"},
            {"jam20", "a..eee\naffg..\nxxdg.i\n..d..i\n..hcci\n..hbbb"},
            {"jam21", "aaed..\nf.ed..\nfxxd..\nfbbb..\n......\n...ccc"},
            {"jam22", "..aeee\nf.ajgg\nfxxj..\n.d.jhh\ncdii.k\ncbbb.k"},
            {"jam23", "..eeei\n..affi\n..axxi\n..gdhh\n..gdcc\n..bbb."},
            {"jam24", "..aff.\n.ga...\ndgxxh.\ndcc.h.\neee.i.\nbb..i."},
            {"jam25", "aaf.gg\nddf..e\njxx.he\njbbbhe\njc.ikk\n.c.ill"},
            {"jam26", ".a.eee\nfa.gk.\nfxxgkd\nhjjjkd\nh.c..i\n..cbbi"},
            {"jam27", "affe..\nagge..\nxxde.i\n..dhhi\n..c..i\n..cbbb"},
            {"jam28", "eeea..\n..jaff\nxxj...\ngdjhhk\ngdbbbk\nccii.k"},
            {"jam29", "eee.j.\n..a.j.\nxxa.jf\ngddhhf\ngcci.k\nbbbi.k"},
            {"jam30", "e.aiii\ne.af..\nexxf..\nggdd.b\n.....b\nhhcc.b"},
            {"jam31", "aa.eee\n...fgg\ndxxf.j\nd.bhhj\nccb..j\n..biii"},
            {"jam32", "aaefgg\n..ef..\nxxe...\ndhhccj\nd..i.j\nbb.i.j"},
            {"jam33", ".ae.ff\n.ae...\nxxe...\nkddhhj\nkccigj\nbbbigj"},
            {"jam34", "a..eee\na..f.j\nxx.fgj\nbbbdgj\n..hdcc\nkkhii."},
            {"jam35", "..eaaj\n..ef.j\nxxef.j\ngbbb..\ngddhc.\nii.hc."},
            {"jam36", "ejjjaa\nefgg.b\nefxx.b\nkkkd.b\n..hdcc\niih..."},
            {"jam37", "aaf.gg\nddf.ej\nbxx.ej\nbkkkej\nb..hcc\nii.hll"},
            {"jam38", "a..eee\naffg..\nxxdg.j\n..dhhj\n..ciij\n..cbbb"},
            {"jam39", "..aeee\n..af..\nxxgf.b\nddghhb\ncijj.b\ncikk.."},
            {"jam40", "eaa.f.\negd.fj\negdxxj\nbbbh.j\n..chii\nkkcll."}};

    for (auto &item : jams)
    {
        std::string k = item.first;
        std::string jam = item.second;

        std::vector<std::vector<char>> grid(6, std::vector<char>(6, '.'));
        std::vector<std::string> lines = split(jam, "\n");
        for (size_t i = 0; i < 6; i++)
        {
            for (size_t j = 0; j < 6; j++)
            {
                grid[i][j] = lines[i][j];
            }
        }

        Metadata metadata(grid);
        std::map<char, size_t> src;
        for (auto car : metadata.cars)
        {
            src[car] = (metadata.orientation[car]) ? metadata.tiles[car][0].first : metadata.tiles[car][0].second;
        }

        auto t1 = std::chrono::high_resolution_clock::now();
        auto &path = solve(src, metadata);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

        std::cout << "solved " << k << " in " << (double) duration / 1e6
            << " seconds (node count = " << metadata.node_count << ")" << std::endl;
    }
}

TEST_CASE("PROJECT RUNTIME TEST", "[project]")
{
    std::map<std::string, std::string> project = {
        {"A00", "AA...O\n.....O\nXX...O\n...QQQ\n....CC\n..RRR."},
        {"A01", "AA...O\nP..Q.O\nPXXQ.O\nP..Q..\nB...CC\nB.RRR."},
        {"A02", "A..OOO\nA..B.P\nXX.BCP\nQQQ.CP\n..D.EE\nFFDGG."},
        {"A03", "......\n......\n.XXO..\n.AAO.P\n.B.O.P\n.BCC.P"},
        {"A04", "O..P..\nO..P..\nOXXP..\n..AQQQ\n..A..B\n..RRRB"},
        {"A05", "AA.O.B\nP..OQB\nPXXOQG\nPRRRQG\nD...EE\nD...FF"},
        {"A06", "AA.B..\nCC.BOP\n.XXQOP\nDDEQOP\nF.EQ..\nF..RRR"},
        {"A07", ".ABBCD\n.A.ECD\n.XXE.F\n..II.F\n...H..\n...H.."},
        {"A08", "...AAO\n..BBCO\nXXDECO\nFFDEGG\nHHIPPP\nKKIQQQ"},
        {"A09", ".ABBCC\n.A.DEE\nXX.DOF\nPQQQOF\nP.G.OH\nP.G..H"},
        {"A10", "AAB.CC\nDDB..O\nPXX..O\nPQQQ.O\nP..EFF\nGG.EHH"},
        {"B11", "OAAP..\nO..P..\nOXXP..\n..BQQQ\n..B..E\n..RRRE"},
        {"B12", "ABB..O\nA.P..O\nXXP..O\n..PQQQ\n....C.\nRRR.C."},
        {"B13", "AABBC.\n..D.CO\n.EDXXO\nPE.FFO\nP..GHH\nPIIGKK"},
        {"B14", "AAB...\n..BCC.\nDEXXFG\nDEHHFG\n..IJJ.\nKKI..."},
        {"B15", ".AABB.\nCCDDOP\nQRXXOP\nQREFOP\nQREFGG\n.HHII."},
        {"B16", "AABBCO\nD.EECO\nDFPXXO\n.FPQQQ\n..P...\nGG...."},
        {"B17", "AOOO..\nA.BBCC\nXXD...\nEEDP..\nQQQPFG\nRRRPFG"},
        {"B18", "AABO..\nCCBO..\nPXXO..\nPQQQ..\nPDD...\nRRR..."},
        {"B19", "..ABB.\n..A.J.\n.DXXJ.\n.DEEF.\n.OOOF.\n......"},
        {"B20", "A..OOO\nABBC..\nXXDC.P\n..D..P\n..EFFP\n..EQQQ"},
        {"C21", "AABO..\nP.BO..\nPXXO..\nPQQQ..\n......\n...RRR"},
        {"C22", "..AOOO\nB.APCC\nBXXP..\n.D.PEE\nFDGG.H\nFQQQ.H"},
        {"C23", "..OOOP\n..ABBP\n..AXXP\n..CDEE\n..CDFF\n..QQQ."},
        {"C24", "..ABB.\n.CA...\nDCXXE.\nDFF.E.\nOOO.G.\nCC..G."},
        {"C25", "AAB.CC\nDDB..O\nPXX.EO\nPQQQEO\nPF.GHH\n.F.GII"},
        {"C26", ".A.OOO\nBA.CP.\nBXXCPD\nERRRPD\nE.F..G\n..FHHG"},
        {"C27", "ABBO..\nACCO..\nXXDO.P\n..DEEP\n..F..P\n..FRRR"},
        {"C28", "OOO.P.\n..A.P.\nXXA.PB\nCDDEEB\nCFFG.H\nRRRG.H"},
        {"C29", "O.APPP\nO.AB..\nOXXB..\nCCDD.Q\n.....Q\nEEFF.Q"},
        {"D30", "AA.OOO\n...BCC\nDXXB.P\nD.QEEP\nFFQ..P\n..QRRR"},
        {"D31", "AAOBCC\n..OB..\nXXO...\nDEEFFP\nD..K.P\nHH.K.P"},
        {"D32", ".AR.BB\n.AR...\nXXR...\nIDDEEP\nIFFGHP\nQQQGHP"},
        {"D33", "A..RRR\nA..B.P\nXX.BCP\nQQQDCP\n..EDFF\nIIEHH."},
        {"D34", "..OAAP\n..OB.P\nXXOB.P\nKQQQ..\nKDDEF.\nGG.EF."},
        {"D35", "OPPPAA\nOBCC.Q\nOBXX.Q\nRRRD.Q\n..EDFF\nGGE..."}
    };

    for (auto &item : project)
    {
        std::string k = item.first;
        std::string jam = item.second;

        std::vector<std::vector<char>> grid(6, std::vector<char>(6, '.'));
        std::vector<std::string> lines = split(jam, "\n");
        for (size_t i = 0; i < 6; i++)
        {
            for (size_t j = 0; j < 6; j++)
            {
                grid[i][j] = lines[i][j];
            }
        }

        Metadata metadata(grid);
        std::map<char, size_t> src;
        for (auto car : metadata.cars)
        {
            src[car] = (metadata.orientation[car]) ? metadata.tiles[car][0].first : metadata.tiles[car][0].second;
        }

        auto t1 = std::chrono::high_resolution_clock::now();
        auto &path = solve(src, metadata);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

        std::cout << "solved " << k << " in " << (double) duration / 1e6
            << " seconds (node count = " << metadata.node_count << ")" << std::endl;
    }
}
