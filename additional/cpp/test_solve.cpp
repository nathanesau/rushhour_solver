#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "solve.h"

TEST_CASE("RUNTIME TEST", "[jams]")
{
    // test solve using jam1
    std::string jam = "bb...g\na..c.g\naxxc.g\na..c..\ne...ff\ne.ddd.";

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
            << "seconds (node count = " << metadata.node_count << ")" << std::endl;
    }
}
