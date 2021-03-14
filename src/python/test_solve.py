from solve import *


jams = {
    "jam1": "bb...g\na..c.g\naxxc.g\na..c..\ne...ff\ne.ddd.",
    "jam2": "a..eee\na..f.j\nxx.fgj\nbbb.gj\n..d.hh\nccdii.",
    "jam3": "......\n......\n.xxb..\n.aab.e\n.c.b.e\n.cdd.e",
    "jam4": "c..e..\nc..e..\ncxxe..\n..abbb\n..a..d\n..fffd",
    "jam5": "aa.e.f\nj..ebf\njxxebi\njgggbi\nd...hh\nd...cc",
    "jam6": "aa.f..\ngg.fej\n.xxbej\nddhbej\nc.hb..\nc..iii",
    "jam7": ".aeefd\n.a.gfd\n.xxg.c\n..hh.c\n...b..\n...b..",
    "jam8": "...aae\n..ffge\nxxdhge\nccdhii\nkkljjj\nmmlbbb",
    "jam9": ".affgg\n.a.dhh\nxx.dec\njbbbec\nj.i.ek\nj.i..k",
    "jam10": "aaf.gg\nddf..e\njxx..e\njbbb.e\nj..hcc\nii.hkk",
    "jam11": "daag..\nd..g..\ndxxg..\n..ebbb\n..e..f\n..cccf",
    "jam12": "aee..d\na.g..d\nxxg..d\n..gbbb\n....f.\nccc.f.",
    "jam13": "aaffg.\n..d.ge\n.hdxxe\njh.cce\nj..ibb\njkkill",
    "jam14": "aaf...\n..f.gg\ndhxxci\ndhkkci\n..j.bb\neej...",
    "jam15": ".aaff.\nggddej\nbkxxej\nbkhcej\nbkhcii\n.llmm.",
    "jam16": "aaffge\nd.hhge\ndcjxxe\n.cjbbb\n..j...\nii....",
    "jam17": "aeee..\na.ffgg\nxxd...\nhhdj..\nbbbjci\nkkkjci",
    "jam18": "aafe..\nggfe..\nhxxe..\nhbbb..\nhdd...\nccc...",
    "jam19": "..aee.\n..a.f.\n.cxxf.\n.cggb.\n.dddb.\n......",
    "jam20": "a..eee\naffg..\nxxdg.i\n..d..i\n..hcci\n..hbbb",
    "jam21": "aaed..\nf.ed..\nfxxd..\nfbbb..\n......\n...ccc",
    "jam22": "..aeee\nf.ajgg\nfxxj..\n.d.jhh\ncdii.k\ncbbb.k",
    "jam23": "..eeei\n..affi\n..axxi\n..gdhh\n..gdcc\n..bbb.",
    "jam24": "..aff.\n.ga...\ndgxxh.\ndcc.h.\neee.i.\nbb..i.",
    "jam25": "aaf.gg\nddf..e\njxx.he\njbbbhe\njc.ikk\n.c.ill",
    "jam26": ".a.eee\nfa.gk.\nfxxgkd\nhjjjkd\nh.c..i\n..cbbi",
    "jam27": "affe..\nagge..\nxxde.i\n..dhhi\n..c..i\n..cbbb",
    "jam28": "eeea..\n..jaff\nxxj...\ngdjhhk\ngdbbbk\nccii.k",
    "jam29": "eee.j.\n..a.j.\nxxa.jf\ngddhhf\ngcci.k\nbbbi.k",
    "jam30": "e.aiii\ne.af..\nexxf..\nggdd.b\n.....b\nhhcc.b",
    "jam31": "aa.eee\n...fgg\ndxxf.j\nd.bhhj\nccb..j\n..biii",
    "jam32": "aaefgg\n..ef..\nxxe...\ndhhccj\nd..i.j\nbb.i.j",
    "jam33": ".ae.ff\n.ae...\nxxe...\nkddhhj\nkccigj\nbbbigj",
    "jam34": "a..eee\na..f.j\nxx.fgj\nbbbdgj\n..hdcc\nkkhii.",
    "jam35": "..eaaj\n..ef.j\nxxef.j\ngbbb..\ngddhc.\nii.hc.",
    "jam36": "ejjjaa\nefgg.b\nefxx.b\nkkkd.b\n..hdcc\niih...",
    "jam37": "aaf.gg\nddf.ej\nbxx.ej\nbkkkej\nb..hcc\nii.hll",
    "jam38": "a..eee\naffg..\nxxdg.j\n..dhhj\n..ciij\n..cbbb",
    "jam39": "..aeee\n..af..\nxxgf.b\nddghhb\ncijj.b\ncikk..",
    "jam40": "eaa.f.\negd.fj\negdxxj\nbbbh.j\n..chii\nkkcll."
}


def test_runtime():
    print("\n")
    for k, jam in jams.items():
        grid = [list(line) for line in jam.splitlines()]
        cl = set([t for r in grid for t in r if t != '.'])
        tl = dict((c, [(i, j) for i in range(6) for j in range(6)
                       if grid[i][j] == c]) for c in cl)
        v = dict((car, tl[car][0][0] != tl[car][1][0]) for car in cl)
        src = dict((car, tl[car][0][0] if v[car] else tl[car][0][1])
                   for car in cl)
        metadata = Metadata(grid)
        start = datetime.now()
        path = solve(src, metadata)
        end = datetime.now()
        print((f"solved {k} in {(end-start).microseconds/1e6} seconds "
               f"(node_count = {metadata.node_count})"))
