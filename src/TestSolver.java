import java.util.Map;
import java.util.Map.Entry;

import rushhour.Solver;

public class TestSolver {
 
    public static void main(String[] args) {
        
        Map<String, String> jams = Map.ofEntries(
            Map.entry("jam01", "bb...g\na..c.g\naxxc.g\na..c..\ne...ff\ne.ddd."),
            Map.entry("jam02", "a..eee\na..f.j\nxx.fgj\nbbb.gj\n..d.hh\nccdii."),
            Map.entry("jam03", "......\n......\n.xxb..\n.aab.e\n.c.b.e\n.cdd.e"),
            Map.entry("jam04", "c..e..\nc..e..\ncxxe..\n..abbb\n..a..d\n..fffd"),
            Map.entry("jam05", "aa.e.f\nj..ebf\njxxebi\njgggbi\nd...hh\nd...cc"),
            Map.entry("jam06", "aa.f..\ngg.fej\n.xxbej\nddhbej\nc.hb..\nc..iii"),
            Map.entry("jam07", ".aeefd\n.a.gfd\n.xxg.c\n..hh.c\n...b..\n...b.."),
            Map.entry("jam08", "...aae\n..ffge\nxxdhge\nccdhii\nkkljjj\nmmlbbb"),
            Map.entry("jam09", ".affgg\n.a.dhh\nxx.dec\njbbbec\nj.i.ek\nj.i..k"),
            Map.entry("jam10", "aaf.gg\nddf..e\njxx..e\njbbb.e\nj..hcc\nii.hkk"),
            Map.entry("jam11", "daag..\nd..g..\ndxxg..\n..ebbb\n..e..f\n..cccf"),
            Map.entry("jam12", "aee..d\na.g..d\nxxg..d\n..gbbb\n....f.\nccc.f."),
            Map.entry("jam13", "aaffg.\n..d.ge\n.hdxxe\njh.cce\nj..ibb\njkkill"),
            Map.entry("jam14", "aaf...\n..f.gg\ndhxxci\ndhkkci\n..j.bb\neej..."),
            Map.entry("jam15", ".aaff.\nggddej\nbkxxej\nbkhcej\nbkhcii\n.llmm."),
            Map.entry("jam16", "aaffge\nd.hhge\ndcjxxe\n.cjbbb\n..j...\nii...."),
            Map.entry("jam17", "aeee..\na.ffgg\nxxd...\nhhdj..\nbbbjci\nkkkjci"),
            Map.entry("jam18", "aafe..\nggfe..\nhxxe..\nhbbb..\nhdd...\nccc..."),
            Map.entry("jam19", "..aee.\n..a.f.\n.cxxf.\n.cggb.\n.dddb.\n......"),
            Map.entry("jam20", "a..eee\naffg..\nxxdg.i\n..d..i\n..hcci\n..hbbb"),
            Map.entry("jam21", "aaed..\nf.ed..\nfxxd..\nfbbb..\n......\n...ccc"),
            Map.entry("jam22", "..aeee\nf.ajgg\nfxxj..\n.d.jhh\ncdii.k\ncbbb.k"),
            Map.entry("jam23", "..eeei\n..affi\n..axxi\n..gdhh\n..gdcc\n..bbb."),
            Map.entry("jam24", "..aff.\n.ga...\ndgxxh.\ndcc.h.\neee.i.\nbb..i."),
            Map.entry("jam25", "aaf.gg\nddf..e\njxx.he\njbbbhe\njc.ikk\n.c.ill"),
            Map.entry("jam26", ".a.eee\nfa.gk.\nfxxgkd\nhjjjkd\nh.c..i\n..cbbi"),
            Map.entry("jam27", "affe..\nagge..\nxxde.i\n..dhhi\n..c..i\n..cbbb"),
            Map.entry("jam28", "eeea..\n..jaff\nxxj...\ngdjhhk\ngdbbbk\nccii.k"),
            Map.entry("jam29", "eee.j.\n..a.j.\nxxa.jf\ngddhhf\ngcci.k\nbbbi.k"),
            Map.entry("jam30", "e.aiii\ne.af..\nexxf..\nggdd.b\n.....b\nhhcc.b"),
            Map.entry("jam31", "aa.eee\n...fgg\ndxxf.j\nd.bhhj\nccb..j\n..biii"),
            Map.entry("jam32", "aaefgg\n..ef..\nxxe...\ndhhccj\nd..i.j\nbb.i.j"),
            Map.entry("jam33", ".ae.ff\n.ae...\nxxe...\nkddhhj\nkccigj\nbbbigj"),
            Map.entry("jam34", "a..eee\na..f.j\nxx.fgj\nbbbdgj\n..hdcc\nkkhii."),
            Map.entry("jam35", "..eaaj\n..ef.j\nxxef.j\ngbbb..\ngddhc.\nii.hc."),
            Map.entry("jam36", "ejjjaa\nefgg.b\nefxx.b\nkkkd.b\n..hdcc\niih..."),
            Map.entry("jam37", "aaf.gg\nddf.ej\nbxx.ej\nbkkkej\nb..hcc\nii.hll"),
            Map.entry("jam38", "a..eee\naffg..\nxxdg.j\n..dhhj\n..ciij\n..cbbb"),
            Map.entry("jam39", "..aeee\n..af..\nxxgf.b\nddghhb\ncijj.b\ncikk.."),
            Map.entry("jam40", "eaa.f.\negd.fj\negdxxj\nbbbh.j\n..chii\nkkcll.")
        );


        for (Entry<String, String> entry : jams.entrySet()) {
            String k = entry.getKey();
            String jam = entry.getValue();

            double startTime = System.currentTimeMillis();
            Solver.solveJam(jam);
            double endTime = System.currentTimeMillis();

            System.out.printf("solved %s in %.2f seconds\n", k, (endTime - startTime) / 1000);
        }
    }
}
