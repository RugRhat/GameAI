using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

[RequireComponent(typeof(NavMeshAgent))]
public class AgentBehavior : MonoBehaviour
{
    [SerializeField] float pursuitRange;

    [SerializeField] Material wanderMaterial;
    [SerializeField] Material pursueMaterial;
    [SerializeField] Material fleeMaterial;

    NavMeshAgent navAgent;

    enum Task { Wandering, Pursuing, Attacking, Fleeing };
    Task currentTask;

    GameObject player;

    GameObject[] pointsOfInterest;

    Vector3 targetLocation;

    // Start is called before the first frame update
    void Start()
    {
        navAgent = GetComponent<NavMeshAgent>();
        navAgent.updateUpAxis = false;
        navAgent.updateRotation = false;

        player = FindObjectOfType<PlayerMovement>().gameObject;

        pointsOfInterest = GameObject.FindGameObjectsWithTag("POI");

        currentTask = Task.Wandering;
 
        SelectNewTargetLocation();
    }

    // Update is called once per frame
    void Update()
    {
        SelectTask();
    }

    void SelectTask()
    {
        PlayerBehavior.State playerState = FindObjectOfType<PlayerBehavior>().CurrentState;

        if(playerState == PlayerBehavior.State.Predator) { Flee(); }
        else if(playerState == PlayerBehavior.State.Prey)
        {
            if(PlayerInRange(pursuitRange)) { Pursue(); }
            else { Wander(); }
        }
    }

    bool PlayerInRange(float range)
    {
        Vector3 agentLocation = gameObject.transform.position;
        Vector3 playerLocation = player.transform.position;

        if(Vector3.Distance(agentLocation, playerLocation) <= range) { return true; }

        return false;
    }

    void SelectNewTargetLocation()
    {
        Vector3 newTargetLocation = player.transform.position;

        if(!(currentTask == Task.Pursuing))
        {
            int rand = Random.Range(0, pointsOfInterest.Length - 1);

            if(pointsOfInterest[rand].transform.position != targetLocation) 
            { 
                newTargetLocation = pointsOfInterest[rand].transform.position; 
            }

            else 
            { 
                newTargetLocation = pointsOfInterest[rand + 1].transform.position; 
            }
        }

        targetLocation = newTargetLocation;
        navAgent.destination = targetLocation;
    }

    bool AtTargetLocation()
    {
        Vector3 agentLocation = gameObject.transform.position;

        if(Vector3.Distance(agentLocation, targetLocation) <= 0.5f) { return true; }
        
        return false;
    }

    void Wander()
    {
        if(currentTask == Task.Wandering && !AtTargetLocation()) 
        { 
            navAgent.destination = targetLocation;
        }

        else 
        { 
            currentTask = Task.Wandering;

            gameObject.GetComponent<MeshRenderer>().material = wanderMaterial;

            SelectNewTargetLocation(); 
        }
    }

    void Pursue()
    {
        if(currentTask == Task.Pursuing && !AtTargetLocation()) 
        { 
            navAgent.destination = player.transform.position;;
        }

        else
        {
            currentTask = Task.Pursuing;

            gameObject.GetComponent<MeshRenderer>().material = pursueMaterial;

            SelectNewTargetLocation(); 
        }
    }

    void Flee()
    {
        if(currentTask == Task.Fleeing && !AtTargetLocation())
        {
            navAgent.destination = targetLocation;
        }

        else 
        {
            currentTask = Task.Fleeing;

            gameObject.GetComponent<MeshRenderer>().material = fleeMaterial;

            SelectNewTargetLocation();
        }
    }
}
