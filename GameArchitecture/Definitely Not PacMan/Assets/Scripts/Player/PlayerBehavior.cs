using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PlayerBehavior : MonoBehaviour
{
    [SerializeField] float predatorDuration; 

    public enum State { Prey, Predator };

    private State currentState;
    public State CurrentState { get { return currentState; } }

    private int score;
    public int Score { get { return score; } }

    GameObject[] agents;

    // Start is called before the first frame update
    void Start()
    {
        currentState = State.Prey;

        agents = GameObject.FindGameObjectsWithTag("Agent");
    }

    // Update is called once per frame
    void Update()
    {
        // Toggle predator state when P key is pressed
        if(Input.GetKeyDown(KeyCode.P))
        {
            StartCoroutine(BecomePredator());
        }
    }

    // Change player state to predator for specified amount of time
    IEnumerator BecomePredator()
    {
        currentState = State.Predator;

        yield return new WaitForSeconds(predatorDuration);

        currentState = State.Prey;
    }

    void OnCollisionEnter(Collision other) 
    {
        if(other.gameObject.tag == "Agent")
        {
            if(currentState == State.Prey) 
            { 
                SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);               // Reset scene if player is "killed" by agent
            }
            else if(currentState == State.Predator) 
            { 
                other.gameObject.SetActive(false);                                              // "Kill" agent
                score ++;
                Debug.Log("Score: " + score);
                if(score == agents.Length)
                {
                    SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);           // Reset scene if player has "killed" all agents
                }
            }
        }

        // else if(other.gameObject.tag == "Power")
        // {
        //     StartCoroutine(BecomePredator());
        // }    

        // else if(other.gameObject.tag == "Gem")
        // {
        //     // Add score;
        // }
    }
}
