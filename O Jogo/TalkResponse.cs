using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class TalkScript : MonoBehaviour {

    public GameObject yusef, masha;
    public float shift, normal, dot, comma;
    public Text target;
    public string[] aux = new string[4];
    public string[] answers = new string[3];

    private static int opinion = 0;

    void Start()
    {

        target.text = "";
        typeText("Iterative");
        typeText("Suitable");

    }

    // Update is called once per frame
    void Update()
    {

    }

    void switchBackground()
    {
        if (!yusef.activeSelf)
        {
            yusef.SetActive(true);
            masha.SetActive(false);
        }
        else
        {
            yusef.SetActive(false);
            masha.SetActive(true);
        }
    }

    IEnumerator print(string[] aux, int i)
    {

        foreach (char letra in aux[i].ToCharArray())
        {

            target.text += letra;

            if (letra == '.')
                yield return new WaitForSeconds(dot);
            else if (letra == ',')
                yield return new WaitForSeconds(comma);
            else if (letra == '~')
            {
                switchBackground();
                if (yusef.activeSelf)
                    target.color = Color.blue;
                else
                    target.color = Color.red;
                yield return new WaitForSeconds(normal);
            }

            else
                yield return new WaitForSeconds(normal);
                
        }

        yield return new WaitForSeconds(shift);

        target.text = ""; 		
    }

    void typeText(string k)
    {
        int i;
        // In this case, the string will be chosen according to user opinion
        if (k == "Suitable")
        {

            if (opinion > 1)
                i = 0;
            else if (opinion > -1)
                i = 1;
            else
                i = 2;

            StartCoroutine(print(answers, i));

        }
        else if (k == "Iterative") // Otherwise (like in the introduction) run through all the array printing content
        {

            for (i = 0; i < aux.Length; i++)
                StartCoroutine(print(aux, i));
            StopCo
        }
    }

}
