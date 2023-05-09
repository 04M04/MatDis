import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';
import 'package:matdis_control/application/points/points_bloc.dart';

import 'custom_points_field_vertical.dart';

class CustomPointsFieldArranged extends StatelessWidget {
  const CustomPointsFieldArranged({super.key});

  @override
  Widget build(BuildContext context) {
    final pointsBlock = PointsBloc();
    return Column(
      mainAxisAlignment: MainAxisAlignment.spaceEvenly,
      children: [
        Row(
          mainAxisAlignment: MainAxisAlignment.spaceEvenly,
          children: [
            CustomPointsFieldVertical(
              onReset: () {
                if (kDebugMode) {
                  print("field 1 resetPressed");
                }
                pointsBlock
                    .add(const PointsResetRequestedEvent(pointsFieldId: 1));
              },
              onAdd: () {
                if (kDebugMode) {
                  print("field 1 addPressed");
                }
                pointsBlock
                    .add(const PointsAddRequestedEvent(pointsFieldId: 1));
              },
              onRemove: () {
                if (kDebugMode) {
                  print("field 1 removePressed");
                }
                pointsBlock
                    .add(const PointsRemoveRequestedEvent(pointsFieldId: 1));
              },
              color: Colors.redAccent,
              points: 0,
            ),
            CustomPointsFieldVertical(
              onReset: () {
                if (kDebugMode) {
                  print("field 2 resetPressed");
                }
              },
              onAdd: () {
                if (kDebugMode) {
                  print("field 2 addPressed");
                }
              },
              onRemove: () {
                if (kDebugMode) {
                  print("field 2 removePressed");
                }
              },
              color: Colors.redAccent,
              points: 0,
            ),
          ],
        ),
        Row(
          mainAxisAlignment: MainAxisAlignment.spaceEvenly,
          children: [
            CustomPointsFieldVertical(
              onReset: () {
                if (kDebugMode) {
                  print("field 3 resetPressed");
                }
              },
              onAdd: () {
                if (kDebugMode) {
                  print("field 3 addPressed");
                }
              },
              onRemove: () {
                if (kDebugMode) {
                  print("field 3 removePressed");
                }
              },
              color: Colors.blueAccent,
              points: 0,
            ),
            CustomPointsFieldVertical(
              onReset: () {
                if (kDebugMode) {
                  print("field 4 resetPressed");
                }
              },
              onAdd: () {
                if (kDebugMode) {
                  print("field 4 addPressed");
                }
              },
              onRemove: () {
                if (kDebugMode) {
                  print("field 4 removePressed");
                }
              },
              color: Colors.blueAccent,
              points: 0,
            ),
          ],
        ),
      ],
    );
  }
}
