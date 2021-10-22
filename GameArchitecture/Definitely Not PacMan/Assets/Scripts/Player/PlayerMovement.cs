using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Rigidbody))]
public class PlayerMovement : MonoBehaviour
{
    [SerializeField] float speed = 10f; 

    Rigidbody rigidbodyRef;

    float horizontalSpeed;
    float verticalSpeed;

    // Start is called before the first frame update
    void Start()
    {
        rigidbodyRef = GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    void Update()
    {
        if(rigidbodyRef == null) { return; }

        horizontalSpeed = Input.GetAxisRaw("Horizontal") * speed;
        verticalSpeed = Input.GetAxisRaw("Vertical") * speed;
    }

    void FixedUpdate() 
    {
        if(rigidbodyRef == null) { return; }
        rigidbodyRef.velocity = new Vector3(horizontalSpeed, 0, verticalSpeed);
    }
}
