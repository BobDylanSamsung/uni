using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RotateAroundPoint : MonoBehaviour
{

    public Transform pivotObject;
    public Transform originalObject;
    public Transform targetObject;
    
    Vector3 originalPosition;
    Vector3 targetPosition;
    Vector3 pivotPosition;
    Vector3 axis;

    float rotationSpeed;          // Speed of rotation in degrees per second
    float desiredRotationAngle;   // Total angle to rotate

    private float currentRotationAngle = 0f;   // Keep track of how much we've rotated so far

    void Start()
    {
        originalPosition = originalObject.position;
        targetPosition = targetObject.position;
        pivotPosition = pivotObject.position;
        axis = CalculatePlaneNormal(originalPosition, targetPosition, pivotPosition);
        desiredRotationAngle = CalculateRotationAngle(originalPosition, targetPosition, pivotPosition);
        rotationSpeed = desiredRotationAngle; // will take 1 second to move
    }

    void Update()
    {
        if (currentRotationAngle < desiredRotationAngle)
        {
            // Calculate how much we should rotate this frame
            float rotationThisFrame = rotationSpeed * Time.deltaTime;
            
            // If this rotation would take us past the desired angle, clamp it
            if (currentRotationAngle + rotationThisFrame > desiredRotationAngle)
            {
                rotationThisFrame = desiredRotationAngle - currentRotationAngle;
            }

            transform.RotateAround(pivotPosition, axis, rotationThisFrame);
            currentRotationAngle += rotationThisFrame;
        }
    }

    Vector3 CalculatePlaneNormal(Vector3 original, Vector3 target, Vector3 pivot)
    {
        Vector3 vectorAB = original - pivot;
        Vector3 vectorAC = target - pivot;

        return Vector3.Cross(vectorAB, vectorAC).normalized;
    }

    float CalculateRotationAngle(Vector3 original, Vector3 target, Vector3 pivot)
    {
        Vector3 vectorAB = original - pivot;
        Vector3 vectorAC = target - pivot;

        return Vector3.Angle(vectorAB, vectorAC);
    }

    void OnDrawGizmos()
    {
        Gizmos.color = Color.red;
        Gizmos.DrawSphere(originalPosition, 0.1f);  // Draws a red sphere at originalPosition

        Gizmos.color = Color.green;
        Gizmos.DrawSphere(targetPosition, 0.1f);  // Draws a green sphere at targetPosition

        Gizmos.color = Color.blue;
        Gizmos.DrawSphere(pivotPosition, 0.1f);  // Draws a blue sphere at pivotPosition
    }
}
