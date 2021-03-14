import java.util.Map;
import java.util.Map.Entry;

import rushhour.Solver;

/**
 * Show runtime for each test case
 */
public class TestSolver {
 
    static void testSolveJams() {

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
            Solver.solve(jam);
            double endTime = System.currentTimeMillis();

            System.out.printf("solved %s in %.2f seconds\n", k, (endTime - startTime) / 1000);
        }
    }

    static void testSolveProject() {

        Map<String, String> project = Map.ofEntries(
            Map.entry("A00", "AA...O\n.....O\nXX...O\n...QQQ\n....CC\n..RRR."),
            Map.entry("A01", "AA...O\nP..Q.O\nPXXQ.O\nP..Q..\nB...CC\nB.RRR."),
            Map.entry("A02", "A..OOO\nA..B.P\nXX.BCP\nQQQ.CP\n..D.EE\nFFDGG."),
            Map.entry("A03", "......\n......\n.XXO..\n.AAO.P\n.B.O.P\n.BCC.P"),
            Map.entry("A04", "O..P..\nO..P..\nOXXP..\n..AQQQ\n..A..B\n..RRRB"),
            Map.entry("A05", "AA.O.B\nP..OQB\nPXXOQG\nPRRRQG\nD...EE\nD...FF"),
            Map.entry("A06", "AA.B..\nCC.BOP\n.XXQOP\nDDEQOP\nF.EQ..\nF..RRR"),
            Map.entry("A07", ".ABBCD\n.A.ECD\n.XXE.F\n..II.F\n...H..\n...H.."),
            Map.entry("A08", "...AAO\n..BBCO\nXXDECO\nFFDEGG\nHHIPPP\nKKIQQQ"),
            Map.entry("A09", ".ABBCC\n.A.DEE\nXX.DOF\nPQQQOF\nP.G.OH\nP.G..H"),
            Map.entry("A10", "AAB.CC\nDDB..O\nPXX..O\nPQQQ.O\nP..EFF\nGG.EHH"),
            Map.entry("B11", "OAAP..\nO..P..\nOXXP..\n..BQQQ\n..B..E\n..RRRE"),
            Map.entry("B12", "ABB..O\nA.P..O\nXXP..O\n..PQQQ\n....C.\nRRR.C."),
            Map.entry("B13", "AABBC.\n..D.CO\n.EDXXO\nPE.FFO\nP..GHH\nPIIGKK"),
            Map.entry("B14", "AAB...\n..BCC.\nDEXXFG\nDEHHFG\n..IJJ.\nKKI..."),
            Map.entry("B15", ".AABB.\nCCDDOP\nQRXXOP\nQREFOP\nQREFGG\n.HHII."),
            Map.entry("B16", "AABBCO\nD.EECO\nDFPXXO\n.FPQQQ\n..P...\nGG...."),
            Map.entry("B17", "AOOO..\nA.BBCC\nXXD...\nEEDP..\nQQQPFG\nRRRPFG"),
            Map.entry("B18", "AABO..\nCCBO..\nPXXO..\nPQQQ..\nPDD...\nRRR..."),
            Map.entry("B19", "..ABB.\n..A.J.\n.DXXJ.\n.DEEF.\n.OOOF.\n......"),
            Map.entry("B20", "A..OOO\nABBC..\nXXDC.P\n..D..P\n..EFFP\n..EQQQ"),
            Map.entry("C21", "AABO..\nP.BO..\nPXXO..\nPQQQ..\n......\n...RRR"),
            Map.entry("C22", "..AOOO\nB.APCC\nBXXP..\n.D.PEE\nFDGG.H\nFQQQ.H"),
            Map.entry("C23", "..OOOP\n..ABBP\n..AXXP\n..CDEE\n..CDFF\n..QQQ."),
            Map.entry("C24", "..ABB.\n.CA...\nDCXXE.\nDFF.E.\nOOO.G.\nCC..G."),
            Map.entry("C25", "AAB.CC\nDDB..O\nPXX.EO\nPQQQEO\nPF.GHH\n.F.GII"),
            Map.entry("C26", ".A.OOO\nBA.CP.\nBXXCPD\nERRRPD\nE.F..G\n..FHHG"),
            Map.entry("C27", "ABBO..\nACCO..\nXXDO.P\n..DEEP\n..F..P\n..FRRR"),
            Map.entry("C28", "OOO.P.\n..A.P.\nXXA.PB\nCDDEEB\nCFFG.H\nRRRG.H"),
            Map.entry("C29", "O.APPP\nO.AB..\nOXXB..\nCCDD.Q\n.....Q\nEEFF.Q"),
            Map.entry("D30", "AA.OOO\n...BCC\nDXXB.P\nD.QEEP\nFFQ..P\n..QRRR"),
            Map.entry("D31", "AAOBCC\n..OB..\nXXO...\nDEEFFP\nD..K.P\nHH.K.P"),
            Map.entry("D32", ".AR.BB\n.AR...\nXXR...\nIDDEEP\nIFFGHP\nQQQGHP"),
            Map.entry("D33", "A..RRR\nA..B.P\nXX.BCP\nQQQDCP\n..EDFF\nIIEHH."),
            Map.entry("D34", "..OAAP\n..OB.P\nXXOB.P\nKQQQ..\nKDDEF.\nGG.EF."),
            Map.entry("D35", "OPPPAA\nOBCC.Q\nOBXX.Q\nRRRD.Q\n..EDFF\nGGE...")
        );

        for (Entry<String, String> entry : project.entrySet()) {
            String k = entry.getKey();
            String jam = entry.getValue();

            double startTime = System.currentTimeMillis();
            String instruction = Solver.solve(jam);
            double endTime = System.currentTimeMillis();

            System.out.printf("solved %s in %.2f seconds\n", k, (endTime - startTime) / 1000);
        }
    }

    public static void main(String[] args) {
        
        testSolveJams();
        testSolveProject();
    }
}
