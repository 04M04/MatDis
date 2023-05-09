import 'package:flutter/material.dart';
import 'package:matdis_control/application/advicer/advicer_bloc.dart';
import 'package:flutter_bloc/flutter_bloc.dart';

class CustomPointsFieldVertical extends StatelessWidget {
  final Color color;
  final int points;
  final Function onReset;
  final Function onAdd;
  final Function onRemove;
  const CustomPointsFieldVertical(
      {super.key,
      required this.onReset,
      required this.onAdd,
      required this.onRemove,
      required this.color,
      required this.points});

  @override
  Widget build(BuildContext context) {
    final themeData = Theme.of(context);

    return Container(
      width: 160,
      height: 280,
      child: Stack(
        clipBehavior: Clip.none,
        children: [
          Center(
            child: InkResponse(
              onLongPress: () => onReset(),
              child: Material(
                elevation: 10,
                borderRadius: BorderRadius.circular(30),
                color: color,
                child: Container(
                    decoration: BoxDecoration(
                      borderRadius: BorderRadius.circular(30),
                    ),
                    width: 160,
                    height: 160,
                    // color: color,
                    child: Center(
                      child: Text(
                        points.toString(),
                        style: const TextStyle(
                            color: Colors.white,
                            fontSize: 70,
                            fontWeight: FontWeight.normal),
                      ),
                    )),
              ),
            ),
          ),
          Positioned(
            top: 0,
            left: 30,
            child: InkResponse(
              onTap: () => onAdd(),
              child: Material(
                color: Colors.white60,
                elevation: 10,
                borderRadius: BorderRadius.all(Radius.circular(20)),
                child: Container(
                  width: 100,
                  height: 100,
                  decoration: const BoxDecoration(
                    borderRadius: BorderRadius.all(Radius.circular(20)),
                  ),
                  child: const Icon(
                    Icons.add,
                    color: Colors.white,
                    size: 70,
                  ),
                ),
              ),
            ),
          ),
          Positioned(
            bottom: 0,
            left: 30,
            child: InkResponse(
              onTap: () => onRemove(),
              child: Material(
                color: Colors.white38,
                elevation: 10,
                borderRadius: BorderRadius.all(Radius.circular(20)),
                child: Container(
                  width: 100,
                  height: 100,
                  decoration: const BoxDecoration(
                    borderRadius: BorderRadius.all(Radius.circular(20)),
                  ),
                  child: const Icon(
                    Icons.remove,
                    color: Colors.white,
                    size: 70,
                  ),
                ),
              ),
            ),
          ),
        ],
      ),
    );
  }
}
