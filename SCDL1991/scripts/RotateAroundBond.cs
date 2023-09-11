using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RotateAroundBond : MonoBehaviour
{
    public Transform bond;
    public Transform pivotAtom;
    // Start is called before the first frame update
    float desiredRotationAngle = 180f;
    private float currentRotationAngle = 0f;   // Keep track of how much we've rotated so far
    Vector3 axis;
    float delay = 1;
    float timer;
    void Start()
    {
        axis = bond.up;
    }

    // Update is called once per frame
    void Update()
    {
        timer += Time.deltaTime;
        axis = bond.up;
        if (currentRotationAngle < desiredRotationAngle && timer > delay)
        {
            // Calculate how much we should rotate this frame
            float rotationThisFrame = desiredRotationAngle * Time.deltaTime;
            
            // If this rotation would take us past the desired angle, clamp it
            if (currentRotationAngle + rotationThisFrame > desiredRotationAngle)
            {
                rotationThisFrame = desiredRotationAngle - currentRotationAngle;
            }

            transform.RotateAround(pivotAtom.position, axis, rotationThisFrame);
            currentRotationAngle += rotationThisFrame;
        }
    }
}
