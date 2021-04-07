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
        level_type src;
        for (auto car : metadata.cars)
        {
            int car_int = (int) car - 97;
            src[car_int] = (metadata.orientation[car]) ? metadata.tiles[car][0].first : metadata.tiles[car][0].second;
        }

        auto t1 = std::chrono::high_resolution_clock::now();
        auto path = solve(src, metadata);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

        std::cout << "solved " << k << " in " << (double) duration / 1e6
            << " seconds (node count = " << metadata.node_count << ")" << std::endl;
    }
}

TEST_CASE("PROJECT RUNTIME TEST", "[project]")
{
    std::map<std::string, std::string> project = {
        {"a00", "aa...o\n.....o\nxx...o\n...qqq\n....cc\n..rrr."},
        {"a01", "aa...o\np..q.o\npxxq.o\np..q..\nb...cc\nb.rrr."},
        {"a02", "a..ooo\na..b.p\nxx.bcp\nqqq.cp\n..d.ee\nffdgg."},
        {"a03", "......\n......\n.xxo..\n.aao.p\n.b.o.p\n.bcc.p"},
        {"a04", "o..p..\no..p..\noxxp..\n..aqqq\n..a..b\n..rrrb"},
        {"a05", "aa.o.b\np..oqb\npxxoqg\nprrrqg\nd...ee\nd...ff"},
        {"a06", "aa.b..\ncc.bop\n.xxqop\nddeqop\nf.eq..\nf..rrr"},
        {"a07", ".abbcd\n.a.ecd\n.xxe.f\n..ii.f\n...h..\n...h.."},
        {"a08", "...aao\n..bbco\nxxdeco\nffdegg\nhhippp\nkkiqqq"},
        {"a09", ".abbcc\n.a.dee\nxx.dof\npqqqof\np.g.oh\np.g..h"},
        {"a10", "aab.cc\nddb..o\npxx..o\npqqq.o\np..eff\ngg.ehh"},
        {"b11", "oaap..\no..p..\noxxp..\n..bqqq\n..b..e\n..rrre"},
        {"b12", "abb..o\na.p..o\nxxp..o\n..pqqq\n....c.\nrrr.c."},
        {"b13", "aabbc.\n..d.co\n.edxxo\npe.ffo\np..ghh\npiigkk"},
        {"b14", "aab...\n..bcc.\ndexxfg\ndehhfg\n..ijj.\nkki..."},
        {"b15", ".aabb.\nccddop\nqrxxop\nqrefop\nqrefgg\n.hhii."},
        {"b16", "aabbco\nd.eeco\ndfpxxo\n.fpqqq\n..p...\ngg...."},
        {"b17", "aooo..\na.bbcc\nxxd...\needp..\nqqqpfg\nrrrpfg"},
        {"b18", "aabo..\nccbo..\npxxo..\npqqq..\npdd...\nrrr..."},
        {"b19", "..abb.\n..a.j.\n.dxxj.\n.deef.\n.ooof.\n......"},
        {"b20", "a..ooo\nabbc..\nxxdc.p\n..d..p\n..effp\n..eqqq"},
        {"c21", "aabo..\np.bo..\npxxo..\npqqq..\n......\n...rrr"},
        {"c22", "..aooo\nb.apcc\nbxxp..\n.d.pee\nfdgg.h\nfqqq.h"},
        {"c23", "..ooop\n..abbp\n..axxp\n..cdee\n..cdff\n..qqq."},
        {"c24", "..abb.\n.ca...\ndcxxe.\ndff.e.\nooo.g.\nhh..g."},
        {"c25", "aab.cc\nddb..o\npxx.eo\npqqqeo\npf.ghh\n.f.gii"},
        {"c26", ".a.ooo\nba.cp.\nbxxcpd\nerrrpd\ne.f..g\n..fhhg"},
        {"c27", "abbo..\nacco..\nxxdo.p\n..deep\n..f..p\n..frrr"},
        {"c28", "ooo.p.\n..a.p.\nxxa.pb\ncddeeb\ncffg.h\nrrrg.h"},
        {"c29", "o.appp\no.ab..\noxxb..\nccdd.q\n.....q\neeff.q"},
        {"d30", "aa.ooo\n...bcc\ndxxb.p\nd.qeep\nffq..p\n..qrrr"},
        {"d31", "aaobcc\n..ob..\nxxo...\ndeeffp\nd..k.p\nhh.k.p"},
        {"d32", ".ar.bb\n.ar...\nxxr...\niddeep\niffghp\nqqqghp"},
        {"d33", "a..rrr\na..b.p\nxx.bcp\nqqqdcp\n..edff\niiehh."},
        {"d34", "..oaap\n..ob.p\nxxob.p\nkqqq..\nkddef.\ngg.ef."},
        {"d35", "opppaa\nobcc.q\nobxx.q\nrrrd.q\n..edff\ngge..."}
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
        level_type src;
        for (auto car : metadata.cars)
        {
            int car_int = (int) car - 97;
            src[car_int] = (metadata.orientation[car]) ? metadata.tiles[car][0].first : metadata.tiles[car][0].second;
        }

        auto t1 = std::chrono::high_resolution_clock::now();
        auto path = solve(src, metadata);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

        std::cout << "solved " << k << " in " << (double) duration / 1e6
            << " seconds (node count = " << metadata.node_count << ")" << std::endl;
    }
}
