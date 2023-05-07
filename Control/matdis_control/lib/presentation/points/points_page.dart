import 'package:matdis_control/application/points/points_bloc.dart';
import 'package:matdis_control/presentation/points/points_error_message.dart';
import 'package:matdis_control/presentation/points/widgets/points_field.dart';
import 'package:matdis_control/presentation/points/widgets/custom_points_field_horizontal.dart';
import 'package:matdis_control/presentation/points/widgets/custom_points_field_vertical.dart';
import 'package:flutter/material.dart';
import 'package:flutter_bloc/flutter_bloc.dart';

class PointsPage extends StatelessWidget {
  const PointsPage({super.key});

  @override
  Widget build(BuildContext context) {
    final themeData = Theme.of(context);
    return Scaffold(
      appBar: AppBar(
        centerTitle: true,
        title: Text(
          "Matdis Control",
          style: themeData.textTheme.displayLarge,
        ),
      ),
      body: Center(
        child: Padding(
          padding: const EdgeInsets.symmetric(horizontal: 50),
          child: Column(
            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            children: [
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                children: [
                  CustomPointsFieldVertical(
                    color: Colors.redAccent,
                    points: 4,
                  ),
                  CustomPointsFieldVertical(
                    color: Colors.redAccent,
                    points: 4,
                  ),
                ],
              ),
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                children: [
                  CustomPointsFieldVertical(
                    color: Colors.blueAccent,
                    points: 4,
                  ),
                  CustomPointsFieldVertical(
                    color: Colors.blueAccent,
                    points: 4,
                  ),
                ],
              ),
            ],
          ),
        ),
      ),
    );
  }
}
