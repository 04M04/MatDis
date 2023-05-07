import 'package:flutter/material.dart';
import 'package:matdis_control/application/advicer/advicer_bloc.dart';
import 'package:flutter_bloc/flutter_bloc.dart';

class CustomPointsFieldVertical extends StatelessWidget {
  final Color color;
  final int points;
  const CustomPointsFieldVertical(
      {super.key, required this.color, required this.points});

  @override
  Widget build(BuildContext context) {
    final themeData = Theme.of(context);

    return InkResponse(
      // onTap: () =>
      //     BlocProvider.of<AdvicerBloc>(context).add(AdviceRequestedEvent()),
      child: Stack(
        clipBehavior: Clip.none,
        // overflow: Overflow.visible,
        children: [
          Card(
            elevation: 1,
            color: color,
            child: Container(
                width: 120,
                height: 120,
                child: Center(
                  child: Text(
                    points.toString(),
                    style: const TextStyle(
                        color: Colors.white,
                        fontSize: 50,
                        fontWeight: FontWeight.normal),
                  ),
                )),
          ),
          const Positioned(
              top: -40,
              left: 30,
              child: Card(
                elevation: 3,
                color: Colors.white70,
                child: SizedBox(
                  width: 60,
                  height: 60,
                  child: Center(
                    child: Icon(
                      Icons.add,
                      color: Colors.white,
                      size: 40,
                    ),
                  ),
                ),
              )),
          const Positioned(
            bottom: -40,
            left: 30,
            child: Card(
              elevation: 3,
              color: Colors.white38,
              child: SizedBox(
                width: 60,
                height: 60,
                child: Center(
                  child: Icon(
                    Icons.remove,
                    color: Colors.white,
                    size: 40,
                  ),
                ),
              ),
            ),
          )
        ],
      ),
    );
  }
}
