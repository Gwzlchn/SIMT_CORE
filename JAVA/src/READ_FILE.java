import java.io.*;
import java.util.Vector;

public class READ_FILE {
    private Vector<INSTRUCTION> m_ins;

    READ_FILE(String file_name){
        m_ins = new Vector<>();
        File file = new File(file_name);
        if(file.exists()){
            try {
                FileReader fileReader = new FileReader(file);
                BufferedReader br = new BufferedReader(fileReader);
                String lineContent = null;
                while((lineContent = br.readLine())!=null){
                    m_ins.add(new INSTRUCTION(lineContent));
                }
                br.close();
                fileReader.close();
            } catch (FileNotFoundException e) {
                System.out.println("no this file");
                e.printStackTrace();
            } catch (IOException e) {
                System.out.println("io exception");
                e.printStackTrace();
            }
        }


    }


    public Vector<INSTRUCTION> get_ins() {
        return m_ins;
    }
}
